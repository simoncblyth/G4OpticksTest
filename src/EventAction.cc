/*
 * Copyright (c) 2019 Opticks Team. All Rights Reserved.
 *
 * This file is part of Opticks
 * (see https://bitbucket.org/simoncblyth/opticks).
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License.  
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 */

#include <string>
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4HCtable.hh"
#include "G4ThreeVector.hh"
#include "EventAction.hh"

#ifdef WITH_ROOT
#include "RootIO.hh"
#endif

#include "Event.hh"
#include <vector> 
#include "PhotonHit.hh"

#ifdef WITH_OPTICKS
#include "OpticksFlags.hh"
#include "G4Opticks.hh"
#include "G4OpticksHit.hh"
#endif

#include "Ctx.hh"
#include "ConfigurationManager.hh"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

EventAction::EventAction(Ctx* ctx_)
:
ctx(ctx_) {
    CaTSEvt = new Event();
}

void EventAction::BeginOfEventAction(const G4Event* anEvent) {
    enable_IO = ConfigurationManager::getInstance()->isWriteHits();
    ctx->setEvent(anEvent);
    CaTSEvt->SetEventNr(anEvent->GetEventID());
}

void EventAction::EndOfEventAction(const G4Event* event) {
    G4HCofThisEvent* HCE = event->GetHCofThisEvent();
    assert(HCE);
    std::vector<G4VHit*> hitsVector;
    std::map<G4String, std::vector<G4VHit* > >* hcmap = CaTSEvt->GetHCMap();
    if (ConfigurationManager::getInstance()->isEnable_opticks()) {

#ifdef WITH_OPTICKS
        G4Opticks* g4ok = G4Opticks::Get();
        G4int eventid = event->GetEventID();

        g4ok->propagateOpticalPhotons(eventid);

        G4OpticksHit hit ;
        G4OpticksHitExtra hit_extra ;

        unsigned num_gensteps = g4ok->getNumGensteps();  
        unsigned num_photons = g4ok->getNumPhotons();  
        unsigned num_hits = g4ok->getNumHit();  
        bool way_enabled = g4ok->isWayEnabled() ;

        G4cout << "EventAction::EndOfEventAction"
                << " eventid " << eventid
                << " num_gensteps " << num_gensteps
                << " num_photons " << num_photons
                << " num_hits " << num_hits
                << " way_enabled " << way_enabled
                << G4endl;

        G4OpticksHitExtra* hit_extra_ptr = way_enabled ? &hit_extra : NULL ;

        for (unsigned i = 0; i < num_hits; i++) 
        {
            g4ok->getHit(i, &hit, hit_extra_ptr );             

            if (enable_IO) {
                hitsVector.push_back(new PhotonHit(i,
                        0,
                        hit.wavelength,
                        hit.time,
                        hit.global_position,
                        hit.global_direction,
                        hit.global_polarization));
            }
        }
        if (enable_IO) {
            hcmap->insert(std::make_pair("PhotonDetector", hitsVector));
        }
        g4ok->reset();
#endif 
    }
    //
    // Now we deal with The geant4 Hit collections. 
    //
    // G4cout << "Number of collections:  " << HCE->GetNumberOfCollections() << G4endl;
#ifdef WITH_ROOT
    if (enable_IO) {
        for (int i = 0; i < HCE->GetNumberOfCollections(); i++) {
            hitsVector.clear();
            G4VHitsCollection* hc = HCE->GetHC(i);
            G4String hcname = hc->GetName();
            std::vector<std::string> y = split(hcname, '_');
            std::string Classname = y[1];
            if (verbose) {
                G4cout << "Classname: " << Classname << G4endl;
            }
            if (Classname == "lArTPC") {
                G4int NbHits = hc->GetSize();
                for (G4int ii = 0; ii < NbHits; ii++) {
                    G4VHit* hit = hc->GetHit(ii);
                    lArTPCHit* Hit = dynamic_cast<lArTPCHit*> (hit);
                    hitsVector.push_back(Hit);
                }
                hcmap->insert(std::make_pair(hcname, hitsVector));
            } else if (Classname == "Photondetector") {
                G4int NbHits = hc->GetSize();
                if (verbose) G4cout << "Photondetector size: " << hc->GetSize() << G4endl;
                for (G4int ii = 0; ii < NbHits; ii++) {
                    G4VHit* hit = hc->GetHit(ii);
                    PhotonHit* Hit = dynamic_cast<PhotonHit*> (hit);
                    hitsVector.push_back(Hit);
                }
                hcmap->insert(std::make_pair(hcname, hitsVector));
            } else {
                G4cout << "SD type: " << Classname << " unknown" << G4endl;
            }
        }
        RootIO::GetInstance()->Write(CaTSEvt);
    }
#endif

    CaTSEvt->Reset();
}


target_sources(${name} 
   PRIVATE
      ColorReader.cc
      ConfigurationManager.cc
      ConfigurationManagerMessenger.cc
      Ctx.cc
      DetectorConstruction.cc
      Event.cc
      EventAction.cc
      G4.cc
      PhotonHit.cc
      PhotonSD.cc
      PrimaryGeneratorAction.cc
      RadiatorSD.cc
      RunAction.cc
      SteppingAction.cc
      TrackerSD.cc
      TrackingAction.cc
      lArTPCHit.cc
      lArTPCSD.cc
)

if(ROOT_FOUND)
target_sources(${name} PRIVATE RootIO.cc)
endif()



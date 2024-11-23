#include "SteppingAction.hh"
#include "HistoManager.hh"

#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "G4RegionStore.hh"
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction()
:G4UserSteppingAction()
{
fScoringRegion1 = G4RegionStore::GetInstance()->FindOrCreateRegion("region1");
}
SteppingAction::~SteppingAction()
{ }
void SteppingAction::UserSteppingAction(const G4Step* step)

{
	if(step->GetTrack()->GetVolume()->GetLogicalVolume()->GetRegion() == fScoringRegion1) {

		G4StepPoint* preStep = step->GetPreStepPoint();
		G4ThreeVector pos = preStep->GetPosition();

		G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
		G4double  x = pos.x()/mm;
 		analysisManager->FillNtupleDColumn(0, x);
		G4double   y = pos.y()/mm;
 		analysisManager->FillNtupleDColumn(1, y);
		G4double   z = pos.z()/mm;
 		analysisManager->FillNtupleDColumn(2, z);
		G4double   Energy = preStep->GetKineticEnergy()/eV;
 		analysisManager->FillNtupleDColumn(3, Energy);
		G4double   Time = step->GetTrack()->GetGlobalTime()/nm;
 		analysisManager->FillNtupleDColumn(4, Time);
		G4int      pdg = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
 		analysisManager->FillNtupleIColumn(5, pdg);

		analysisManager->AddNtupleRow();
	}
	return;
}

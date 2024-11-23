#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4Region;

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction();
	~SteppingAction();
	
	virtual void UserSteppingAction(const G4Step*);

private:
	G4Region*  fScoringRegion1;
};
#endif

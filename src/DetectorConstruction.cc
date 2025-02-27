//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file eventgenerator/particleGun/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
//
// $Id: DetectorConstruction.cc 68734 2013-04-05 09:47:02Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "DetectorConstruction.hh"


#include "G4RegionStore.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),fWorldSizeXY(0),fWorldSizeZ(0)
{
  fWorldSizeXY = 50*cm;
  fWorldSizeZ  = 50*cm;    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  //
  // define a material
  //   
  G4Material* Air =
  G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"); 
  
  G4Material* Tungsten =
  G4NistManager::Instance()->FindOrBuildMaterial("G4_W");
  
  G4Material* Aluminium = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
  
  //     
  // World
  //
  G4Box*  
  solidWorld = new G4Box("World",                                //its name
                   fWorldSizeXY/2,fWorldSizeXY/2,fWorldSizeZ/2); //its size
                   
  G4LogicalVolume*                         
  logicWorld = new G4LogicalVolume(solidWorld,           //its solid
                                   Air,                  //its material
                                   "World");             //its name
  G4VPhysicalVolume*                                   
  physiWorld = new G4PVPlacement(0,                      //no rotation
                                 G4ThreeVector(),        //at (0,0,0)
                                 logicWorld,             //its logical volume
                                 "World",                //its name
                                 0,                      //its mother  volume
                                 false,                  //no boolean operation
                                 0);                     //copy number
                                 
                      
                
    G4Box *solidCrystal2 = new G4Box("crystal2", 3.0*cm, 3.0*cm, 1.0*cm);
	G4LogicalVolume * lCrystal2 = new G4LogicalVolume(solidCrystal2,Air,"crystal2", 0 ,0,0);
	new G4PVPlacement(0, G4ThreeVector(0.0*cm,0.0*cm,20.0*cm), lCrystal2,"crystal2", logicWorld, false,0);

/////////Barrera
	G4Box *solidBarr=new G4Box("Target", 3.*cm,3.0*cm,0.2*cm);
	G4LogicalVolume * lBarr = new G4LogicalVolume(solidBarr, Aluminium, "Target",0,0,0);
	new G4PVPlacement(0,G4ThreeVector(0.0*cm, 0.0*cm,5.0*cm), lBarr,"Target", logicWorld, false,0);  

//////////phantom///
	G4Box *solidTarget=new G4Box("Target", 5.0*cm,5.0*cm,0.5*cm);
	G4LogicalVolume * lTarget = new G4LogicalVolume(solidTarget, Tungsten, "Target",0,0,0);
	new G4PVPlacement(0,G4ThreeVector(0.0*cm, 0.0*cm,3.0*cm), lTarget,"Target", logicWorld, false,0);            
                
                
                G4Region* region1 = G4RegionStore::GetInstance()->FindOrCreateRegion("region1");
	lCrystal2->SetRegion(region1);
	region1->AddRootLogicalVolume(lCrystal2);
  //
  //always return the physical World
  //  
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

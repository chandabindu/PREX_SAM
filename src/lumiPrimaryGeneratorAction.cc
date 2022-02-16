#include "lumiPrimaryGeneratorAction.hh"
#include "lumiPrimaryGeneratorMessenger.hh"

lumiPrimaryGeneratorAction::lumiPrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(),fParticleGun(NULL),runType(-1){

  primaryMessenger = new lumiPrimaryGeneratorMessenger(this);
  
  G4int noParticles = 1;
  fParticleGun = new G4ParticleGun(noParticles);

  G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.0));
  fParticleGun->SetParticleEnergy(8.8*GeV);

  raster_center_x = 0.0;
  raster_center_y = 0.0;
}

lumiPrimaryGeneratorAction::~lumiPrimaryGeneratorAction(){
  delete primaryMessenger;
  delete fParticleGun;
}
void lumiPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  switch(runType){
  case 0 : 
    GeneratePrimaries_origin(anEvent);
    break;
  case 1 :
    GeneratePrimaries_raster(anEvent);
    break;
  }

}

void lumiPrimaryGeneratorAction::GeneratePrimaries_origin(G4Event* anEvent){
  G4double beam_z = -150*cm;
  
  G4double beam_x = 0*cm;
  G4double beam_y = 0*cm;

  fParticleGun->SetParticlePosition(G4ThreeVector(beam_x,beam_y,beam_z));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}


void lumiPrimaryGeneratorAction::GeneratePrimaries_raster(G4Event* anEvent){
  G4double beam_z = -150*cm;

  G4double beam_x = raster_width*(G4UniformRand())*cm
    -(raster_width/2.0)*cm + raster_center_x*cm;
  G4double beam_y = raster_height*(G4UniformRand())*cm
    -(raster_height/2.0)*cm + raster_center_y*cm;

  fParticleGun->SetParticlePosition(G4ThreeVector(beam_x,beam_y,beam_z));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

void lumiPrimaryGeneratorAction::SetBeamType(G4int type){
  runType = type;
}

void lumiPrimaryGeneratorAction::SetRasterCenterX(G4double x){
  raster_center_x = x;
}

void lumiPrimaryGeneratorAction::SetRasterCenterY(G4double y){
  raster_center_y = y;
}

void lumiPrimaryGeneratorAction::SetRasterWidth(G4double x){
  raster_width = x;
}

void lumiPrimaryGeneratorAction::SetRasterHeight(G4double y){
  raster_height = y;
}

void lumiPrimaryGeneratorAction::SetBeamDirection(G4ThreeVector direction){
  fParticleGun->SetParticleMomentumDirection(direction);
}


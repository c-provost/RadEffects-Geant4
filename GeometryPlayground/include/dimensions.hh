
#include "globals.hh"
#include "G4SystemOfUnits.hh"

namespace PackageDimensions
{

    // ************************************************************************************************
    // Variable Farm. In here is where all the necessary variables for the construction of the geometry
    // are initialized to their default values. These, in theory, should be able to be adjusted with UI
    // command (my current project)                             -Conrad Provost •Monday, April 29, 2024
    // ************************************************************************************************

        // Default parameters for the ConstructionGeometry
    // Dimensions according to MIL-STD-1835D for package construction
    //                    ↓ converting inches to centimeters      
    G4double D = 1.490 * 2.54 * cm;
    G4double E =  .550 * 2.54 * cm;
    G4double A =  .232 * 2.54 * cm;
    G4double Q =  .060 * 2.54 * cm;

    // Height of the package chunk
    G4double height = (A-Q)/2;

    // Cavity Dimensions, as measured by Rob and Myself.
    G4double cavD = .015625 * 2.54 * cm;   // 1/64 of an inch.
    G4double cavL = 27 * cavD;
    G4double cavW = 22 * cavD;

    // Wafer Dimensions - Accessed from shotty internet articles.
    G4double waferdepth = 500 * um;
    G4double waferlength = .5 * cm;
    G4double waferwidth = .3 * cm;

    G4double xPosWafer = (3.*cm);
    G4double yPosWafer = (3.*cm);
    G4double zPosWafer = -1*(height/2 - cavD + waferdepth/2);

    // Pack Chunk Dimensions
    G4double packChunkwidth = .8 * cm;
    G4double packChunklength = .6 * cm;
}

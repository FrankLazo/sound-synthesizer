#include <iostream>
#include <vector>
using namespace std;

#include "olcNoiseMaker.h"

const double dPI = 3.14159;
atomic< double > dFrequencyOutput = { 0.0 };

// dTime is time that has passed since the start of the program
double MakeNoise( double dTime )
{
	// Standard tuning: 440Hz; which is an A4 on a keyboard
	// double dOutput = 1.0 * sin( 2 * dPI * 440.0 * dTime );

	// Change the frequency to change the pitch
	double dOutput = 1.0 * sin( 2 * dPI * dFrequencyOutput * dTime );

	// Chord
	// double dOutput = 1.0 * ( sin( 2 * dPI * dFrequencyOutput * dTime ) + sin( 2 * dPI * ( dFrequencyOutput + 50 ) * dTime ) );

	return dOutput * 0.5;

	// Square wave function
	// Like 8-bit sound in old games, consoles and machines
	// if ( dOutput > 0.0 )
	// 	return 0.2;
	// else
	// 	return -0.2;
}

int main()
{
	wcout << "onelonecoder.com - Synthesizer Part 1" << endl;

	// Get all sound hardware
	vector< wstring > devices = olcNoiseMaker< short >::Enumerate();

	// Display findings
	wcout << "\nFound devices\n" << "~~~~~~~~~~~~~" << endl;
	for ( auto device : devices ) wcout << "Found Output Device: " << device << endl;

	// Create sound machine!!
	// First sound device is usually system's default sound device
	// Sample rate = 44100; number of channels = 1
	// Use <short> for more precision on waveform
	// Latency management: 8, 512
	olcNoiseMaker< short > sound( devices[ 0 ], 44100, 1, 8, 512 );

	// Link noise function with sound machine
	// Noise Maker class is constantly running in the background
	sound.SetUserFunction( MakeNoise );

	// Graphic guide
	wcout << "\nThis is your keyboard\n" << "~~~~~~~~~~~~~~~~~~~~~"
		<< "\n(Press <Ctrl + C> to quit)\n" << endl;

	// ┬─┬───┬─┬─┬───┬───┬─┬─┬───┬───┬───┬─┬
	// │ │   │ │ │   │   │ │ │   │   │   │ │
	// │ │ S │ │ │ F │ G │ │ │ J │ K │ L │ │
	// │ └─┬─┘ │ └─┬─┴─┬─┘ │ └─┬─┴─┬─┴─┬─┘ │
	// │   │   │   │   │   │   │   │   │   │
	// │ Z │ X │ C │ V │ B │ N │ M │ , │ . │
	// ┴───┴───┴───┴───┴───┴───┴───┴───┴───┴
	// (=A2)

	wcout << "+-+---+-+-+---+---+-+-+---+---+---+-+" << endl;
	wcout << "| |   | | |   |   | | |   |   |   | |" << endl;
	wcout << "| |   | | |   |   | | |   |   |   | |" << endl;
	wcout << "| | S | | | F | G | | | J | K | L | |" << endl;
	wcout << "| +-+-+ | +-+-+-+-+ | +-+-+-+-+-+-+ |" << endl;
	wcout << "|   |   |   |   |   |   |   |   |   |" << endl;
	wcout << "|   |   |   |   |   |   |   |   |   |" << endl;
	wcout << "| Z | X | C | V | B | N | M | , | . |" << endl;
	wcout << "+---+---+---+---+---+---+---+---+---+" << endl;
	wcout << "(=A2)                       (=A3)\n" << endl;

	// Base Frequency
	double dOctaveBaseFrequency = 110.0; // A2
	double d12thRootOf2 = pow( 2.0, 1.0 / 12.0 );

	while ( 1 )
	{
		// Add a keyboard like a piano

		bool bKeyPressed = false;

		for ( int k = 0; k < 15 ; k++ )
		{
			// & 0x8000: key is pressed
			if ( GetAsyncKeyState( (unsigned char)( "ZSXCFVGBNJMK\xbcL\xbe"[ k ] ) ) & 0x8000 )
			{
				dFrequencyOutput = dOctaveBaseFrequency * pow( d12thRootOf2, k );
				bKeyPressed = true;
			}
		}

		if ( !bKeyPressed )
		{
			dFrequencyOutput = 0.0;
		}
	}

	return 0;
}

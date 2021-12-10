# Sound Synthesizer

<a id="index"></a>

This project is an exercise from this [Youtube tutorial][VideoTutorial] by [javidx9][YTChannel]. The following text is made up of notes from that tutorial and some personal notes.

## About this project

This code is written to be accessible, it's not written to be the most optimal or intelligent way to solve the problem.

The header file `olcNoiseMaker.h` access the sound hardware creating a thread in the background and presenting that with a hook to apply data to the sound card.

## Concepts

**Sound** is made up of [**sine waves**][SineWave] of different **frequencies** and **amplitudes**.
**Low frequencies** are **bass** and **high frenquencies** are **treble**.
**Amplitude** is like amplitude of **loudness**.

We need to represent the sound waveform as smoothly as possible but a computer just store numbers digitally to a fixed amount of precision.
We can emulate this by applying another functions ([See graphics][Graphics]).

**Nyquist's theorem**: we need a **sample rate** which is double the highest frequency we want to record in our sound synthesis.
**Human hearing range** is about 20Hz to 20kHz (wavelength from 17 meters to 1.7 centimeters).

Another possible waves are **square**, **triangle** and **sawtooth** waves.

## About C++

These are new knowledge for me in this project about C++ language.

```c++
// Header file must be included only once
// Doesn't work in all compilers
#pragma once
```

```c++
// Linker
// Just in Visual Studio
#pragma comment(lib, "winmm.lib")

// With gcc or g++
// $ g++ test.cpp -o test.exe -lWinmm
```

```c++
// std::find
#include <algorithm>

auto p = find( vector.begin(), vector.end(), "value to find" );
```

```c++
// Standard output stream oriented to wide characters
wcout << "Some wide characters" << endl;

// String class for wide characters
wstring someString = L"Something";

// Wide char to wstring
wchar_t wc = L'C';
wstring ws = { wc };
```

```c++
// Convert char *string to wchar_t *string

// strlen
#include <string>

const char *origin = "Some string";
size_t newsize = strlen( origin ) + 1;
wchar_t *wcstring = new wchar_t[ newsize ];

// convert
size_t convertedChars = 0;
mbstowcs_s( &convertedChars, wcstring, newsize, character, _TRUNCATE );
```

```c++
// Variables for use in different threads
// Initialization must be between curly braces
atomic< double > someAtom = { 0.0 };
```

```c++
#include <Windows.h>

// If 'A' key is pressed
// For pressed key: 0x8000
// Bit by bit comparison (&)
// GetAsyncKeyState return a 16-bit signed value
if( GetAsyncKeyState( 'A' ) & 0x8000 );
```

## About Visual Studio

First time in Visual Studio:

1. Create a new project
1. Empty Project
1. Project name (not Place solution and...)

Default project structure:

```
# Solution 'SoundSynthesizer'
│
└ # SoundSynthesizer
    │
    ├ # References/
    ├ # External Dependencies/
    ├ # Header Files/
    ├ # Resource Files/
    └ # Source Files/
```

Before first time run program:

1. Project: ProjectName Properties
1. Linker: Input
1. Additional Dependencies: winmm.lib;

Compile and run:

1. Build: Build ProjectName (`Ctrl + B`)
1. Local Windows Debugger

[Arriba][Index]

<!-- ## Resources
<https://www.cplusplus.com/>
<https://docs.microsoft.com/en-us/>
[Graphing Calculator](https://www.desmos.com/calculator?lang=en) -->

[VideoTutorial]:    https://www.youtube.com/watch?v=tgamhuQnOkM
[YTChannel]:        https://www.youtube.com/channel/UC-yuWVUplUJZvieEligKBkA
[SineWave]:         https://en.wikipedia.org/wiki/Sine_wave
[Graphics]:         https://www.desmos.com/calculator/vefvp1xfjz
[Index]:            #index

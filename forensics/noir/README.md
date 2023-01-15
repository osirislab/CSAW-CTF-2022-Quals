# noir

## Notice to OSIRISLab 2022 team
Hey this is Richard, basically this challenge is from Wen from the 2021 CTF and we chose to hold it in reserve as it's a beautiful challenge but hard to avoid the guesswork required to solve it. Wen may use it in a different CTF this year so I want to make it super clear that its inclusion in this repository does not amount to any decision on our part to use it in a future CSAW CTF without consulting him first. We still want this in a shared place so I'm not an information bottleneck, and this repo is the default place to put stuff as of 12/2021.

## Description
I am a forest, and a night of dark trees: but he who is not afraid of my
darkness, will find banks full of roses under my cypresses.

## Solution
The image is a webm encoded as rgb24 rawvideo. This can be transcoded to webm
using ffmpeg. The flag is encoded in the headlights of the train as morse.

## Walkthrough
```
#!/bin/bash

ffmpeg -i noir.png -pix_fmt rgb24 -f rawvideo noir.webm
```

Morse: https://en.wikipedia.org/wiki/Morse_code

The format for the flag in the video is `(flag)sil3nt_refl3ct1on` repeated twice. Note that the open and close parentheses are the same symbol, `-.--.`. 

## Tester notes
Tester 1:
The challenge is advanced, and it will be great to see the contestants work on it. I would suggest giving a hint if they cannot solve it. 
I tested the first version in which the flag is in base64 format in the video title tag. 
I am currently testing the updated challenge with blinking lights and working with Wen to verify since I am new to morse code.

Tester 2: 
The first symbol is cut off a little, so that instead of `-.--.` it reads like `..--.`. But the message repeats again, twice.
We added a clarification to the `challenge.json` file that (flag)3x4mpl3 should be replaced with `flag{3x4mpl3}`. 

I am a little concerned that there's a mental leap required to think of pulling a video out of the PNG file. But as the author mentioned,
that's also what makes it novel. We can drop a hint if people are not getting it, although it is also likely that some people will not 
get it and others will, and whether they do is down to this mental leap. So, challenge author, the question is how does a player infer the 
rgb24 rawvideo pattern from the pixels in the image without guessing? That determines whether this is a fun challenge or not, basically.

Tester 3: 
See the Excel spreadsheet translating the Morse back to letters. 
[morse.xlsx](https://github.com/osirislab/CSAW-CTF-2021-Finals/files/7504114/morse.xlsx)
The morse code message repeats a few times in the video. I tried to
note (for most of the characters) the approximate begin/end time for when they're shown in the video based on the timestamp. I was able to 
successfully decode the message to (flag)sil3nt_refl3ct1on.

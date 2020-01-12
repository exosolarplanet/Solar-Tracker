# Solar-Tracker

This project aims to design a dual-axis solar tracker which is able to track an
additional light source in a given environment. The information collected with
4 LDRs are processed with an Arduino Uno microcontroller. The system
is a closed loop system as it includes a LDR circuit as feedback loop.
Two continuous servomotors are attached to Arudino Uno which controls the
movement of the solar tracker in two axes of freedom. Extended information
regarding the code can be found in the Arduino script as comments.

In this specific project, the real-life conditions had been neglected as the aim
was to only track an additional light source. This is the reason why only
continuous servo motors had been used, as speed of tracking the light
was an important factor. However, improvements can be made such as adapting the
script to a real-life application such as rooftop solar panels or solar panel
fields. An easy improvement would be setting the initial position of the
solar tracker to the direction where the sun rises in a given environment.

# SimpleOpenGLInterface
A simple OpenGL interface using Qt5.

- developped under Qt Creator 3.3.0 (Qt 5.4.0).
- tested with Windows and Linux.

Requirements :
- "assets/unnamed.png" in order to show an icon, otherwise, it will shows an ugly magenta colored square.
- icudt53.dll
- icuin53.dll
- icuuc53.dll
- libgcc_s_dw2-1.dll
- libstdc++-6.dll
- libwinpthread-1.dll
- Qt5Cored.dll
- Qt5Guid.dll
- Qt5OpenGLd.dll
- Qt5Widgetsd.dll

It shows :
- a blank square that represents the background (where all manipulations are possible)
- a black square that represents the HUD (where all elements came from)
- an icon (an element)

Functionalities :
- drag & drop an element from HUD to the background, or vice versa
- scale an element on the background by [clic] + [shift] + [movement]
- rotate an element on the background by [clic] + [control] + [movement]

Notes :
- when an element is dragged and dropped from the 'bg' to the 'hud', then it is reinitialized in 'hud' space
- when the [shift] or [control] modifier is released during action when the clic is still pressed, then the action is aborted

![Alt text](preview1.jpg?raw=true "Initial preview")
![Alt text](preview2.jpg?raw=true "After drag and drop preview")
![Alt text](preview3.jpg?raw=true "After drag and drop, scale and rotation preview")

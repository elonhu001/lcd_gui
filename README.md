# lcd_gui
this project is to make a gui for "explorer develop board" of opendev

the I2C i used in this project is not stm32 itself,  i simulate an I2C with PB0 and PF11, all touch file are in touch file

/*********************************************************************************************************/
TODO:there is a bug,  i can't  use tuch function, in the debug process,  i find that i cant read the ID of touch control IC, so i have to get a oscilloscop and check my I2C waveform

2018-9-11
i have find the root of this problem, my main frequncy is different from yuanzi, so my waveform is also diffrent from standard, now i modified my opt_delay(), i can use touch function now, but it is not stable, sometimes i cant use it, i will fix it tomorrow

2018-9-11
good news!! I have fixed this problem,  i use stm32CubeMX configed an I2C, it's not a simulated one, so i don't have to care about the waveform, now it's OK, next time i will try to write an push button to control led.
/*********************************************************************************************************/

2018-9-28(home)

I can use cube MX to light LCD, and use touch screen, also can use STemWin, but when I use STemWin, the frequncy of scanning will be much slower, I don't know how to fix it, now I am learning how to use STemWin create window, and use the programe of Yuanzi to learn this. 

as for the problem of frequncy,  I will fix it later

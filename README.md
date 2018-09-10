# lcd_gui
this project is to make a gui for "explorer develop board" of opendev

the I2C i used in this project is not stm32 itself,  i simulate an I2C with PB0 and PF11, all touch file are in touch file

/*********************************************************************************************************/
TODO:there is a bug,  i can't  use tuch function, in the debug process,  i find that i cant read the ID of touch control IC, so i have to get a oscilloscop and check my I2C waveform

i have find the root of this problem, my main frequncy is different from yuanzi, so my waveform is also diffrent from standard, now i modified my opt_delay(), i can use touch function now, but it is not stable, sometimes i cant use it, i will fix it tomorrow

/*********************************************************************************************************/
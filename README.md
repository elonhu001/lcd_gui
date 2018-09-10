# lcd_gui
this project is to make a gui for "explorer develop board" of opendev

the I2C i used in this project is not stm32 itself,  i simulate an I2C with PB0 and PF11, all touch file are in touch file

TODO:there is a bug,  i can't  use tuch function, in the debug process,  i find that i cant read the ID of touch control IC, so i have to get a oscilloscop and check my I2C waveform
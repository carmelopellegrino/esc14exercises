Exercises on Floating Point representation ans optimization

1) introduction<br>
  compile and run intLoop.cpp and floatLoop.cpp<br>
  explain the result
  
2) limits<br>
  compile and run limits.cpp<br>
  compare what you observe with documentation<br>
  try with double, int, ...

3) number of floats<br>
   count the number of floating points numbers between two given ones<br>
   start from howManyFloats.cpp

4) Kahan summation<br>
   use Kahan summation to make the "patriot clock" precise<br>
   start from patriot.cpp
  
5) second order equation<br>
   write an accurate and fast solution of the second order equation<br>
   start from secondOrder.cpp
   
6) speed<br>
  starting from ptcut.cpp write a fast version of the "pt" and "phi" cut<br>
  the result may change, comment.<br>
  try a fast eta cut<br>
  
7) compiler optimization<br>
  copy past kernels form assocMath.cc into http://gcc.godbolt.org <br>
  change compiler options, observe how the emitted code changes<br>
  try with your own kernels
  

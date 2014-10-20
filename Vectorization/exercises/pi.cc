float pi_reg(int  num_steps)
{
  

   float step = 1.0f/(float(num_steps));
   float sum = 0.0;

   for (int i=1;i<= num_steps; i++){
      auto x = (i-0.5f)*step;
      sum = sum + 4.0f/(1.0f+x*x);
   }

   float pi = step * sum;


   return pi;
}


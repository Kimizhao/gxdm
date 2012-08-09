
#ifndef _scaner_H
#define _scaner_H





void sanner()
{
     if(curr!=currold) //光标位置变化，则更新显示
      {
       DisplayUpdata();
       currold=curr;
      } 
 
   if(!KEY_UP)  
    {
     DelayMs(10);
     if(!KEY_UP)     
    {
        while(!KEY_UP);
      {
    if(curr<4)
     //判断数组中数值个数
     { curr++; }
      }
    }
 }

  if(!KEY_DOWN) 
    {
     DelayMs(10);
       if(!KEY_DOWN)     
         {
           while(!KEY_DOWN);
               {
                    if(curr>0)
                    { curr--; }
                }
          }
     }  



  if(!KEY_TURN) 
    {
     DelayMs(10);
       if(!KEY_TURN)     
         {
		  TU=!TU;
		  	speed_num=speed_num+10;
			 Num_zhuanh(speed_num,2);
           while(!KEY_TURN)
               {
                    if(TU)
                    { LCD_PutString(4,3,TAB5);
				
					}
                    if(!TU)
                    { LCD_PutString(4,3,TAB6);
				//	speed_num=speed_num-10;
					}
				
                }

				
          }
     }  



  if(!KEY_TIMER) 
    {
     DelayMs(10);
       if(!KEY_TIMER)     
         {
           while(!KEY_TIMER);
               {
             timer_num=timer_num+5;
			 Num_zhuanh(timer_num,1);
			 TU=!TU;
			 TURN_FZ(TU);

                }
          }
     }  
	 	 
}

#endif

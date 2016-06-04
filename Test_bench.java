package src;

public class Test_bench {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Car[] car = new Car[6];
		
		
		car[0] = new Audi_a6();
		car[1] = new Chairman(3800, 8842, 240);
		car[2] = new Kanival(3800, 4432, 240);
		car[3] = new Mini(2800, 1009, 280);
		car[4] = new QM3(3000, 1004, 260);
		car[5] = new SM6(3000, 7732, 260);
		
		((Audi_a6)car[0]).setMaxSpeed(280);
		((Audi_a6)car[0]).setID(6666);
		((Audi_a6)car[0]).setDisplayment(3600);

		for(int i = 0; i < car.length; i++)
		{
				car[i].Print();	
		}
		
		for(int i =0; i < car.length; i++)
		{
				car[i].SpeedUP();
		}
		
		car[0].SpeedDown();

		for(int i =0; i < car.length; i++)
		{
			if( car[i] instanceof Domestic)
			{
				((Domestic)car[i]).where_from();;
			}
			else
			{
				((Internal)car[i]).where_from();;
			}
			
		}
		
		for(int i =0; i < car.length; i++)
		{
			if( car[i] instanceof Light)
			{
				((Light)car[i]).what_is_type();
			}
			else if ( car[i] instanceof Medium)
			{
				((Medium)car[i]).what_is_type();
			}
			else
			{
				((Heavy)car[i]).what_is_type();
			}		
		}
	}

}

package src;

public class SM6 extends Medium implements Car, Domestic {

	String nAme = "SM6";
	public int Displayment;
	public int ID;
	public int maxSpeed;
	public int Speed;
	
	public SM6() {
		// TODO Auto-generated constructor stub
	}
	
	public SM6 (int Displayment, int ID, int maxSpeed)
	{
		this.Displayment = Displayment;
		this.ID = ID;
		this.maxSpeed = maxSpeed;
	}
	
	public void Print(){
		System.out.println("Name: "+ this.nAme +" "+"��ⷮ : "+ this.Displayment+" "+"ID: "+ this.ID);
	}

	@Override
	public void SpeedUP() {
		// TODO Auto-generated method stub
		while(Speed < this.maxSpeed)	
		{	
			this.Speed += 30;
			if(Speed > maxSpeed)
				System.out.println(this.nAme+" "+"����ӵ�: "+this.maxSpeed);
			else
				System.out.println(this.nAme+" "+"����ӵ�: "+this.Speed);
		}
		System.out.println(this.nAme+" "+"�ִ� �ӵ� ����  �����ϼ���");

	}

	@Override
	public void SpeedDown() {
		// TODO Auto-generated method stub
				while(Speed > 0)	
				{	
					this.Speed-= 30;
					if(Speed < 0)
						System.out.println(this.nAme+" "+"����ӵ�: "+0);
					else
						System.out.println(this.nAme+" "+"����ӵ�: "+this.Speed);
				}
				System.out.println(this.nAme+" "+"Stop!");


	}
	
	public void Break()
	{
		this.Speed = 0;
	}
	
	public void where_from()
	{	
		System.out.println(this.nAme+": ������.");
	}
	
	public  void what_is_type()
	{
		super.type = "����";
		System.out.println(this.nAme+" "+"�� ����: "+ type);
	}
}

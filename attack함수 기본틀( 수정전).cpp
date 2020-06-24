void attack(){
	int num;
	cout << "무슨 공격을 할까요?" << endl;
	cin >> num;
	switch(num){
		case 1:
			cout << "기본 공격(데미지: 5) " << endl;
			basic attack();
			break; 
		case 2:
			cout << "기본 스킬1(데미지: 10)" << endl;
			skill1(); 
			break;
		case 3:
		    cout << "기본 스킬2 (데미지: 15)"  << endl; 
		    skill2();
		    break;
	}
}

void basic attack()                        //만날시 열리는 전투창으로 이동 나중에  
{
	Monster_Hp = Monster_Hp - 5;
}

void skill1()                             //만날시 열리는 전투창으로 이동 나중에 
{ 
	Monster_Hp = Monster_Hp - 10;
}

void skill2()                              //만날시 열리는 전투창으로 이동 나중에 
{
	Monster_Hp = Monster_Hp - 15;
}

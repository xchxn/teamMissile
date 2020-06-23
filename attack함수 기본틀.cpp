void attack(){
	int num;
	cout << "무슨 공격을 할까요?" << endl;
	cin >> num;
	switch(num){
		case 1:
			cout << "기본 공격(데미지: 5) " << endl;
			break; 
		case 2:
			cout << "기본 스킬1(데미지: 10)" << endl;
			break;
		case 3:
		    cout << "기본 스킬2 (데미지: 15)"  << endl; 
		    break;
	}
}

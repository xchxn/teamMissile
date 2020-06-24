void bag(){
	int num ;
	cout << " 가방을 여시겠습니까? " << endl;     // 수정'
    cout << " 1. 네  " << endl;
	cout << " 2. 아니오 " << endl;
	cin >> num;
	if(num = 1){
		cout << " 멀꺼내시겠습니까? " << endl;
		cout << " 1. 사과 " << endl;
		cout << " 2. 주문서 " << endl; 
		switch(num){
			case 1:
				heal();    // 사과를 먹게 되면 체력 힐       나중에 밑에 힐 함수 만들어야함. 
			case 2: 
				int strup = 10;  // 주문서를 통한 공격력 강화        나중에 밑에 함수 만들어야함. 
				cout << "모든 공격과 스킬에 공격력 10이 붙었습니다." << endl;
		}
		
	} 
}

void heal()             // 나중에 만날시 열리는 전투창에 옮겨야함. 
{
	int hp_up = 10;
	Song_ hp = Song_ hp +10;
	
}


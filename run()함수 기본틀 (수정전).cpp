void run(){
	int num; 
	int num_2;
	cout << "도망가시겠습니까? " << endl;      
	cout << "1. 네 도망가겠습니다." << endl;
	cout << "2. 아니요." << endl;
	cin >> num;
	switch(num){
		case 1:
			selMenu = 5;
		case 2:
			cout<<"1.공격하시겠습니까?" << endl;
			cout<<"2.가방을 여시겠습니까?" << endl;
			cin >> num_2;
			if(num_2 == 1){
				attach();
			}
			if(num_2 == 2){
				bag();
			}
	}	
}


#include"DxLib.h"
#include"Suken.h"
#include"Country.h"
#include"General.h"

void CCountry::Awake(){
	money=100;
}

void CCountry::Pay(int num){
	money-=num;
}

void CCountry::Income(int num){
	money+=num;
}

bool CCountry::CanPay(int require){
	if(money>=require){
		return true;
	}else{
		return false;
	}
}

void CCountry::ShowMoney(int num){
	DrawFormatString(850,25+num*25,YELLOW,"%d",money);
}

int count_less(int money)
{
	int less_money = money - (money % 20);
	return less_money;
}

int count_more(int money)

{
	int more_money = money + (20 - (money % 20));
	return more_money;
} 



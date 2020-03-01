BEGIN { sum_budget = 0; daily_budget = 100; sum_cost = 0; sell_price = 2826; sum_revenue = 0; }
{
    sum_budget += daily_budget;
    if (sum_budget > $1) {
	sum_cost += $1;
	sum_revenue += (sell_price - $1);
	sum_budget -= $1;
    }
}
END { printf "Total:\ncost: %f\nrevenue: %f\nRate of return: %f\n", sum_cost, sum_revenue, sum_revenue / sum_cost }

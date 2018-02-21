
for (( i = 0; i < 60; i++ )); do
	wget http://www.wsj.com/mdc/public/page/2_3021-activnyse-actives.html?mod=topnav_2_3021 --output-document=$(date +%F_%T).html
	sleep 1m
done


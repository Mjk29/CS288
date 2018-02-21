


getViews(){

	viewCount=()
	local i
	local inp

	inp=$(grep -E -o "([0-9]*,*)* views" index3.html | tr -d ',' | rev |cut -c 7- | rev)



	for i in $inp; do
		viewCount+=("$i,")
	done

	echo  ${viewCount[@]}

}



getUName(){

	userName=()
	local inp
	local i

	echo `grep -E -o "data-ytid.*itct=.* >.*</a>" index3.html ` > /tmp/hmw3.txt }


	inp=$(egrep  -o " >(\(*[[:alnum:]]*\.*[[:space:]]*\)*)*<" /tmp/hmw3.txt   | tr ' ' '_' |rev | cut -c 2- | rev |cut -c 3- )




	for i in $inp; do
		echo "$i,"
	done

}






getDuration(){

	local inp
	local i

	inp=$(grep -E -o " Duration: .*\.<" index3.html  | cut -c 11- | rev | cut -c 3- | rev)


	for i in $inp; do
		echo "$i,"
	done

	# echo $inp


}


getTitle(){
	local inp
	local i

	inp=$(grep -E -o " dir=\"ltr\">(.*)</a><span " index3.html | tr ' ' '_' | cut -c 12- | rev | cut -c 11- | rev | tr ',' '`')

	for i in $inp; do
		echo "$i"
	done
}



	VW=$(getViews)
	UN=$(getUName)
	DR=$(getDuration)
	TIT=$(getTitle)

	# getTitle
# 	getDuration
# getUName
# getViews

	userNames=()
	views=()
	durations=()
	titles=()

	for x in $UN; do
		userNames+=($x)
	done

	for y in $VW; do
		views+=($y)
	done

	for z in $DR; do
		durations+=($z)
	done

	for w in $TIT; do
		titles+=($w)
	done


	# for p in ${titles[@]}; do
	# 	echo $p
	# done
	# echo ${titles[@]}



# for ((i=0; i<=${#userNames[@]}; i++)); do
#      printf '%40s %40s \n' "${userNames[i]}" "${views[i]}"
#      printf "${userNames[$i]}     ${views[$i]} \n"
#      # printf "$i"
# done

# paste <(printf "%s\n" "${UN[@]}") <(printf "%s\n" "${views[@]}")

echo -e "\e[7m"
# echo -e "\e[1m"
printf '\n'
paste -d' ' <(printf "%-50.50s\n" "User Name,") <(printf "%-15.15s\n" "Views,") <(printf "%-10.10s\n" "Duration,") <(printf "%-100s\n" "Title,") >> youtube.csv
printf '\n'
echo -e "\e[27m"

paste -d' ' <(printf "%-50.50s\n" "${userNames[@]}") <(printf "%-15.15s\n" "${views[@]}") <(printf "%-10.10s\n" "${durations[@]}") <(printf "%-20s\n" "${titles[@]}") >> youtube.csv

# printf ${TIT[@]}
# echo ${#userNames[@]}
# echo ${#views[@]}
# 	echo ${#titles[@]}



# printf "%25s %25s \n" ${userNames} ${views}




# getUName


# echo $userNames


# printf "%15s\n" "$views" "$userNames \n" | column -t

# echo "${userNames[0]}"
# echo "${uName[@]}"
# echo "${viewCount[@]}"


# printf "%30s %30s\n" $views $userNames
# printf "%24s\n"	$userNames
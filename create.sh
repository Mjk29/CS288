# 	Depth(){

# 		# echo "test in function"
# 		newD="$3/test"
# 		# echo $newD

# 		for (( i = 0; i < $1; i++ )); do

# 			`mkdir $newD`
# 				echo $i
# 				Depth $i $2 $newD

# 		done

# }









# Depth(){

# 	for (( i = 0; i < 3; i++ )); do

# 		temp_open=()
# 		temp_closed=()
# 		for x in open; do
# 			tmp=()
# 			for (( i = 0; i < 3; i++ )); do
# 				tmp=(${tmp[@]} $x / $i)
# 			done
# 		done
# 		tmp_open=(${tmp_open[@]} $tmp[@]})

# 	done
# open=tmp_open

# }



# Breadth(){
# 	echo "    HERE IS THE BREADTH FUNCTION "

# 	openDir=($3)
# 	#echo $1 $2 $3 $4
# 	# `mkdir $3`


# 	for (( i = 0; i < $1; i++ )); do
# 		nOpen=()
# 		echo "i $i"
# 		# temp=()
# 		`mkdir "$3/$i"`

	




# 		# for j in ${openDir[@]}; do
# 		while [[ ${openDir[@]} ]]; do
# 			#statements
		

# 			echo "Initial open directory "
# 			echo "${openDir[@]}"
# 			# `mkdir $3/$j`
# 			echo "  j $j"

			





# 			for (( k = 0; k < $2; k++ )); do
# 				echo "      k $k"
# 				# `mkdir /$3/$i/$k`


# 			# echo	"   jk  $j / $k"

# 			echo "Make this  $3/$i/$k"
# 				`mkdir -p "$3/$i/$k"`

# 				# openDir+=("$j/$k")
# 				openDir=("$3/$i/$k")

# 				# Breadth $i $k "$i/$j/$k"
# 			done


# 			# openDir+=("$3/$i/$k")


# 			echo " openDir is here ${openDir[@]}"



# 		echo "================= "
# 		done

# 	# echo "${openDir[@]}"


# 	done

# 	openDir=(${nOpen[@]})



# 	cat <<- EOF
# 	`tree -C $Dir` "\n"
# 			EOF

# 	`rm -r $Dir`

# }












#Breadth $Depth $Breadth $root
Breadth(){


	openList=()
	# echo "dollar 3 $3"

	for (( i = 0; i < $1; i++ )); do
		# `mkdir $3/$i`
		# openList+=("$3/$i")
		# echo $3/$i
		# d=$(( $1 + $i ))
		# Breadth $d $2 "$3/$i"
	


	for (( j = 0; j < $2; j++ )); do
	# 	echo " Making this directory $3/$j "
		openList+=("$3/$j")
	
		if [[ ! -d "$3/$j" ]]; then
			`mkdir -p $3/$j`
		fi
		
	done
done

	# echo "Here is the openList : ${openList[@]}"

	for x in "${openList[@]}"; do
		# echo "X IS $x"
		D=$(( $1 - 1 ))
		# echo "HERE IS D : $D"
		Breadth $D $2 $x
	done









	# cat <<- EOF
	# `tree -C $Dir` "\n"
	# 		EOF

	# `rm -r $Dir`





}




 # $Depth $Breadth $root
Depth(){


	openList=()
	# echo "dollar 3 $3"

	for x in "{$3[@]}"; do
		echo "$x"
	done
	# 	for (( j = 0; j < $2; j++ )); do
	# 	# 	echo " Making this directory $3/$j "
	# 	openList+=("$3/$j")
	
	# 	if [[ ! -d "$3/$j" ]]; then
	# 		`mkdir -p $3/$j`
	# 	fi
		
	# 	done
	# done

	# # echo "Here is the openList : ${openList[@]}"

	# for x in "${openList[@]}"; do
	# 	# echo "X IS $x"
	# 	D=$(( $1 - 1 ))
	# 	# echo "HERE IS D : $D"
	# 	Breadth $D $2 $x
	# done









	# cat <<- EOF
	# `tree -C $Dir` "\n"
	# 		EOF

	# `rm -r $Dir`

}











if [[ -z $1 ]]; then
echo "Testing directory trees, [m] [n] [directory] [depth / breadth ]"
echo "First number parameter is set to the type you choose \n"
echo -e "Using /tmp as testing directory \n"
fi


	Dir="/tmp/TreeTest"
	m=$1
	n=$2





if [[ $4 == "breadth" ]]; then
	echo "Breadth tree"
	echo $1 $2 $Dir $4
	`mkdir $Dir`

	Breadth $1 $2 $Dir 

	cat <<- EOF
	`tree -C $Dir` "\n"
			EOF

	`rm -r $Dir`

fi



if [[ $4 == "depth" ]]; then
	echo "Depth tree $1 $2"

	`mkdir $Dir`



	Depth $1 $2 $Dir


	#Displays directoy tree using tree
	#If not working, sudo apt-get install tree
	cat <<- EOF
	`tree -C $Dir` "\n"
			EOF

	#Removes created directories
	`rm -r $Dir`


fi


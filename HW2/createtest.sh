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












# #Breadth $Depth $Breadth $root
# Breadth(){

# 	openList=()
# 	# echo "dollar 3 $3"
# 	ass=$3
# 	#While depth is not zero >still have more
# 	for (( i = 0; i < $1; i++ )); do
		
# 		#Add all subdirectories to a list
# 		#for subDir in rootDir
# 			for subDir in "${ass[@]}"; do
# 				echo "testing for subdirectories $subDir" 
# 				subDir+=("$subDir")

# 			done

		
# 			if [[ ! -d "$3/$j" ]]; then
# 				`mkdir -p $3/$j`
# 			fi
			
# 		done
	

# 	# echo "Here is the openList : ${openList[@]}"

# 	for x in "${openList[@]}"; do
# 		# echo "X IS $x"
# 		D=$(( $1 - 1 ))
# 		# echo "HERE IS D : $D"
# 		Breadth $D $2 $x
# 	done









# 	# cat <<- EOF
# 	# `tree -C $Dir` "\n"
# 	# 		EOF

# 	# `rm -r $Dir`





# }







# Depth (){

# 	# echo "depth Tree $1 $2 $3 "
# 	# echo "fourth $4"
	
# 	if [[ -z $4 ]]; then
# 		passDir="$4"
# 	fi

# 	thrid=$3

# 	# echo "making Dir $3 "
# 	# `mkdir $3`

# 	# if [[ $1 == 0 ]]; then
# 	# 	# echo "making $3 "
# 		`mkdir -p $3`

# 	# fi

# 	for (( i = 0; i < $1; i++ )); do
				
# 		# echo "directory $3"
# 		# echo " depth $passDep"
# 				echo "I = $i"
# 				echo "$1"

			
# 		# for (( j = 0; j < $2; j++ )); do
# 		# 	echo "J = $j"

# 		# 	# echo "second run  $3/$j" 
# 		# 	# echo " THis is the currenty place   $3 "
# 		# 	passDir+="$3/$j"
# 		# 	# passDir=(("$3 + $j")
# 		# 	# echo "PASS DIR FUCK $passDir"
# 		# 	passDep=$(( $1 - 1 ))
# 		# 	Depth $passDep $2 $passDir

# 		# done		
# 		# echo " i = $i"

# 			passDir+="$3/$i"
# 			passDep=$(( $1 - 1 ))

# 			Depth $passDep $2 $passDir

# 	done



# 	# for j in $currD; do
# 	# 	echo $j
# 	# done



# }





Depth(){

	local D=$1
	local B=$2
	local currD=$3

	if [ $D -le 0 ]; then 
		return
	fi

	let D--
	local tmpB=$B

	while [[ $tmpB > 0 ]]; do
		echo "Making $currD/$tmpB"
		mkdir -p $currD/$tmpB
		Depth $D $B $currD/$tmpB
		let tmpB--
done



}













if [[ -z $1 ]]; then
echo "Testing directory trees, [m] [n] [directory] [D / breadth ]"
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

	Breadth $1 $2 $Dir $4




	cat <<- EOF
	`tree -C $Dir` "\n"
			EOF

	`rm -r $Dir`

	# openDir=()

	# i=0
	# while [[ i -le $2 ]]; do
		
	# 	openDir=()
	# 	echo $i
	# 	(( i++ ))



	# done

	# for (( i = 0; i < $1; i++ )); do
	# 	openDir+=($i)
	# done

	
	# for x in "${openDir[@]}"; do
	# 	z=0
	# 	for (( i = 0; i < $2; i++ )); do		
	# 		openDir+=($x/$z)
	# 		(( z++ ))
	# 	done
		
	# done

	# # for x in "${openDir[@]}"; do
	# # 	`mkdir /tmp/TreeTest
	# # done



	# echo "${openDir[@]}"


fi



if [[ $4 == "depth" ]]; then
	echo "Depth tree $1 $2 $3 $4"

	`mkdir $Dir`


	Depth $1 $2 $Dir 
	# Depth


	#Displays directoy tree using tree
	#If not working, sudo apt-get install tree
	cat <<- EOF
	`tree -C $Dir` "\n"
			EOF

	#Removes created directories
	`rm -r $Dir`


fi


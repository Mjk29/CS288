
##Matthew Kehoe; 2017 CS288

#Breadth $Depth $Breadth $root
Breadth(){
	openList=()
	for (( i = 0; i < $1; i++ )); do
		for (( j = 0; j < $2; j++ )); do
			openList+=("$3/$j")
			#Checking against already made directory
			if [[ ! -d "$3/$j" ]]; then
				#making directoy, note -p parameter
				#-p creates parent directories for 
				#the current directory
				`mkdir -p $3/$j`
			fi
		done
	done

	#recursive loop for all items on the open list
	for x in "${openList[@]}"; do
		#Depth - 1, bash doesn't like -- for some reason
		D=$(( $1 - 1 ))
		#Recursive call
		Breadth $D $2 $x
	done
}

Depth(){

	# Local defined variables seem to work better
	local D=$1
	local B=$2
	local currD=$3

	# End of depth  check
	if [ $D -le 0 ]; then 
		return
	fi

	# Seems that bash only likes -- on local variable
	let D--
	local tmpB=$B

	while [[ $tmpB > 0 ]]; do
		# -p might not be necessary here
		`mkdir -p $currD/$tmpB`
		Depth $D $B $currD/$tmpB
		let tmpB--
done
}

#checking for parameters
if [[ -z $1 ]]; then
	echo -e "\n[m] [n] [directory] [depth/breadth]"
	echo "First number parameter is set to the type you choose"
	echo "This script defaults to /tmp/\$directory"
	echo -e " \e[7m"
	echo "WARNING THIS SCRIPT USES rm -r TO DELETE THE CREATED DIRECTORY"
	echo "Changing /tmp is not recommended"
	echo -e "\e[0m"
	exit
fi
	
#DO NOT CHANGE /tmp READ WARNING ABOVE
Dir="/tmp/$3"
m=$1
n=$2

if [[ $4 == "breadth" ]]; then
	echo "Breadth tree"
	# echo $1 $2 $Dir $4
	Breadth $1 $2 $Dir $4
fi

if [[ $4 == "depth" ]]; then
	echo "Depth tree "
	# echo $1 $2 $3 $4
	Depth $1 $2 $Dir 

fi

#Displays directoy tree using tree
#If not working, sudo apt-get install tree
#tree --help 
cat <<- EOF
`tree -C  $Dir` "\n"
		EOF

#Removes created directories
`rm -r $Dir`
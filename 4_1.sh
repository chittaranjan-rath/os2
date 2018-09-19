#!bin/bash
echo "the file name is $1"
if [ -f $1 ]; then
	echo "its a reg fiile"
	match=`file $1  | grep -o compressed`
	echo $match


	if [[ $1 =~ \.gz$ ]];
	then	
		tar -xzf $1
	fi
	if [[ $1 =~ \.zip$ ]];
	then	
		unzip $1
	fi	
	if [[ $1 =~ \.7z$ ]];
	then	
		p7zip -d $1
	fi
	if [[ $1 =~ \.tar$ ]];
	then	
		tar -xf $1
	fi
	if [[ $1 =~ \.tar.bz2$ ]];
	then	
		tar -xjf $1
	fi
	if [[ $1 =~ \.bz2$ ]];
	then	
		bunzip2  $1
	fi
	if [[ $1 =~ \.gz$ ]];
	then	
		gunzip -xvf $1
	fi

else
	echo "its not a reg fiile"
fi


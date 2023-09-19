#include"address_book.h"

//动态存储
void init_message(message* mess)
{
	//mess->all_data写成content* all_data，导致无法输入信息
	mess->all_data = (content*)malloc(init_cap * sizeof(content));
	if (mess->all_data == NULL)//不记得要考虑没内存的前提
	{
		perror("init_message");
		return;
	}
	mess->capacity = init_cap;
	mess->available_data = 0;

	//读取信息(不能在主函数add中调用，否则删不掉)
	fread_message(mess);//没在这里调用，导致始终无法读取数据！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
}

void fread_message(message* mess)
{
	content temp = { 0 };
	FILE* pf = fopen("C:\\Users\\张艺兴的圈外女友\\source\\repos\\Project5\\通讯录(动态开辟)\\address_book.txt", "r");
	while (fread(&temp,sizeof(content),1,pf))
	{
		expend_capacity(mess);
		mess->all_data[mess->available_data] = temp;
		mess->available_data++;
	}
	fclose(pf);
	pf = NULL;
}

////初始化通讯录信息
//void init_message(message* mess)
//{
//	mess->available_data = 0;
//	memset(mess->all_data, 0, sizeof(mess->all_data));//memset内存设置(初始化可全0或非全0)
//}

void expend_capacity(message* mess)
{
	if (mess->available_data == mess->capacity)
	{
		//(mess->capacity + add_cap)*sizeof(content)写成mess->capacity + add_cap
		content* ptr = (content*)realloc(mess->all_data, (mess->capacity + add_cap) * sizeof(content));
		if (ptr != NULL)
		{
			mess->all_data = ptr;
			mess->capacity += add_cap;
			printf("扩容成功！\n");
		}
		else
		{
			printf("存储已满，无法添加信息！\n");
		}
	}
}

//动态访问
void add_message(message* mess)
{
	//扩容
	expend_capacity(mess);
	if (isalnum)
	{
		printf("请输入姓名：");
		scanf("%s", mess->all_data[mess->available_data].name);
		printf("请输入性别：");
		scanf("%s", mess->all_data[mess->available_data].sex);//无法读取性别原因：scanf中加了"\n"！！！！！！
		//int i=0;scanf("%d",&i);
		//要取地址
		printf("请输入年龄：");
		scanf("%d", &(mess->all_data[mess->available_data].age));
		printf("请输入联系方式：");
		scanf("%d", &(mess->all_data[mess->available_data].tele));
		printf("请输入住址：");
		scanf("%s", mess->all_data[mess->available_data].address);

	}
	mess->available_data++;//已用空间+1
	printf("输入信息成功！\n");
}

void fwrite_message(message* mess)
{
	int i = 0;
	FILE* pf = fopen("C:\\Users\\张艺兴的圈外女友\\source\\repos\\Project5\\通讯录(动态开辟)\\address_book.txt", "w");
	if (pf == NULL)
	{
		perror("fwrite_message");
		return;
	}
	for ( i = 0; i < mess->available_data; i++)
	{
		//mess->all_data+i:数组名+i该元素的地址
		fwrite(mess->all_data+i, sizeof(content), 1, pf);
	}
	fclose(pf);
	pf = NULL;
}

void release_message(message* mess)
{
	
	free(mess->all_data);
	mess->all_data = NULL;
	mess->available_data = 0;
	mess->capacity = 0;
}

////静态存储
//void add_message(message* mess)
//{
//	if (mess->available_data == max_person)
//	{
//		printf("通讯录可用信息容量已满，无法添加新信息！\n");
//		return;//结束执行，但不用返回值
//	}
//	else
//	{
//		// mess->all_data[mess->available_data]：将可用空间的信息放进总容量对应下标的空间
//		// 把第n个添加进来的信息放在总数据中下标为n的位置
//		// available=1 ==》all_data=1
//		// 例：第0个学生放在下标为0的all_data中
//		printf("请输入姓名：");
//		scanf("%s", mess->all_data[mess->available_data].name);
//		printf("请输入性别：");
//		scanf("%s", mess->all_data[mess->available_data].sex);//无法读取性别原因：scanf中加了"\n"！！！！！！
//		//int i=0;scanf("%d",&i);
//		//要取地址
//		printf("请输入年龄：");
//		scanf("%d", &(mess->all_data[mess->available_data].age));
//		printf("请输入联系方式：");
//		scanf("%d",&(mess->all_data[mess->available_data].tele));
//		printf("请输入住址：");
//		scanf("%s", mess->all_data[mess->available_data].address);
//		mess->available_data++;//已用空间+1
//		printf("输入信息成功！\n");
//	}
//}

void print_message(const message* mess)//根本没想到要固定mess
{
	//打印标题(-左对齐)
	printf("%-8s\t%-8s\t%-8s\t%-20s\t%-20s\n", "姓名", "性别", "年龄", "联系方式", "住址");
	//打印内容
	int i = 0;
	for ( i = 0; i < mess->available_data; i++)
	{
		printf("%-8s\t%-8s\t%-8d\t%-20d\t%-20s\n",//忘记把 "年龄", "联系方式"改为“%d”
			mess->all_data[i].name,//没有考虑到【i】，而是写成all_data.name
			mess->all_data[i].sex,
			mess->all_data[i].age,
			mess->all_data[i].tele,
			mess->all_data[i].address);
	}
}
//static:只能在本源文件用，不能被其他源文件使用
//又是一个想不到的地方
static int find_all_names(message* mess, char name[], int ret[])
{
	int i = 0;
	int j = 0;
	for (i = 0; i < mess->available_data; i++)
	{
		//两个字符串不能直接用等号！！！！！
		if (strcmp(name, mess->all_data[i].name) == 0)
		{
			ret[j] = i;//将所有名字相同的下标存储到一个数组里
			j++;//记录存储在ret数组中的索引数量
		}
	}
	return j;
}

void delete_message(message* mess)
{
	//判断
	if (mess->available_data == 0)
	{
		printf("通讯录为空！无法删除！\n");
		return;
	}
	int* ret = (int*)malloc(mess->capacity * sizeof(int));
	if (ret == NULL)//差点忘了判断
	{
		return;
	}
	//int ret[max_person] = { 0 };//将所有名字相同的下标存储到一个数组里
	char name[max_name] = { 0 };//写成int类型（无语）
	printf("请输入你要删除的(信息)名字：");
	//int改成char之后，%d没改成%s，导致无论输什么，都提示信息不存在！！！！
	scanf("%s", name);
	int count = find_all_names(mess, name, ret);//没考虑到删除、修改、查询都要用到“查找”指令
	if (count == 0)
	{
		printf("你输入的信息不存在！无法删除！\n");
		return;
	}
	//执行
	int i = 0;
	//count:相同名字的数量,for条件要么写成count-1，i>0；要么写成count，i>=0，导致怎么删除都不对！！！
	for (i = count - 1; i >= 0; i--)
	{
		int index = ret[i];//想不到！根本想不到!!!!
		while (index < mess->available_data - 1)
		{
			//available_data - 1,count - 1原因：最后一个数字替换之后，还会出现最后一个数字下标+1的数，栈溢出
			//例：1 2 3 4 5，把1删除后，2覆盖到1的位置，3覆盖2位置，4覆盖3，5覆盖4，如果不减一，会出现5后面的空值覆盖5的情况
			mess->all_data[index] = mess->all_data[index + 1];
			index++;
		}
		mess->available_data--; //--写成++，导致无论怎么删，打印依旧还存在
	}
	printf("删除成功！\n");
	free(ret);//一开始没加进去，私密马赛
	ret = NULL;//这也能忘
}

void search_message(message* mess)
{
	char name[max_name] = { 0 };
	while (1)
	{
		printf("请输入你要查找的名字：");
		scanf("%s", name);
		int* ret = (int*)malloc(mess->capacity * sizeof(int)); 
		if (ret == NULL)//差点忘了判断
		{
			return;
		}
		//int ret[max_person] = { 0 };//想不到，根本想不到！！！！！！
		int count = find_all_names(mess, name, ret);
		if (count == 0)
		{
			printf("你输入的信息不存在！无法查找！\n");
			return;
		}
		else
		{
			printf("已找到信息！\n");
			printf("%-8s\t%-8s\t%-8s\t%-20s\t%-20s\n", "姓名", "性别", "年龄", "联系方式", "住址");
			int i = 0;
			for (i = 0; i < count; i++)
			{
				printf("%-8s\t%-8s\t%-8d\t%-20d\t%-20s\n",
					mess->all_data[ret[i]].name,//ret[i]:将所有名字相同的下标存储到一个数组里
					mess->all_data[ret[i]].sex,
					mess->all_data[ret[i]].age,
					mess->all_data[ret[i]].tele,
					mess->all_data[ret[i]].address);
			}
			break;
		}
		free(ret);
		ret = NULL;
	}
}

void modify_message(message* mess)
{
	char name[max_name] = { 0 };
	printf("请输入你要修改的数据姓名：");
	scanf("%s", name);
	int* ret = (int*)malloc(mess->capacity * sizeof(int));
	if (ret == NULL)//差点忘了判断
	{
		return;
	}
	//int ret[max_person] = { 0 };//想不到，根本想不到！！！！！！
	int count = find_all_names(mess, name, ret);
	int i = 0;
	if (count == 0)
	{
		printf("你输入的信息不存在！无法修改！\n");
		return;
	}
	for (i = 0; i < count; i++) 
	{
		char choice = 0;
		printf("找到第%d个匹配的人，名字是%s。确定修改信息吗(y/n)? 或者继续输入名字：%s 进行查询?\n", i + 1, mess->all_data[ret[i]].name, mess->all_data[ret[i]].name);
		scanf(" %c", &choice); //注意空格，它可以消除缓冲区中的任何空白字符(想不到！根本想不到！！！！)
		if (choice == 'y' || choice == 'Y') 
		{
			printf("请输入姓名：");
			scanf("%s", mess->all_data[ret[i]].name);// ret[i]:将所有名字相同的下标存储到一个数组里
			printf("请输入性别：");
			scanf("%s", mess->all_data[ret[i]].sex);
			printf("请输入年龄：");
			scanf("%d", &(mess->all_data[ret[i]].age));
			printf("请输入联系方式：");
			scanf("%d", &(mess->all_data[ret[i]].tele));
			printf("请输入住址：");
			scanf("%s", mess->all_data[ret[i]].address);
			printf("修改信息成功！\n");
			break;
		}
	}
	if (i == count)
	{
		printf("共%d个数据，已查询完毕，请重新选择！\n",count);
	}
	free(ret);
	ret = NULL;

}

void sort_menu()
{
	printf("*********************\n");
	printf("******* 1.正序 ******\n");
	printf("******* 2.倒序 ******\n");
	printf("*********************\n");
}
void sort1(message* mess)
{
	int i = 0;
	int j = 0;
	int temp_age = 0;
	int temp_tele = 0;
	char temp_name[max_name] = { 0 };
	char temp_sex[max_sex] = { 0 };
	char temp_address[max_address] = { 0 };
	for ( i = 0; i < mess->available_data - 1; i++)
	{
		for ( j = 0; j < mess->available_data - 1 - i; j++)
		{
			if (mess->all_data[j].age > mess->all_data[j + 1].age)
			{
				temp_age = mess->all_data[j].age;//没把name改为age,导致报错
				mess->all_data[j].age = mess->all_data[j + 1].age;
				mess->all_data[j + 1].age = temp_age;

				temp_tele = mess->all_data[j].tele;//没把name改为age,导致报错
				mess->all_data[j].tele = mess->all_data[j + 1].tele;
				mess->all_data[j + 1].tele = temp_tele;

				strcpy(temp_name, mess->all_data[j].name);//不交换name，就显示只交换了年龄，其他信息未排序
				strcpy(mess->all_data[j].name, mess->all_data[j + 1].name);
				strcpy(mess->all_data[j + 1].name, temp_name);

				strcpy(temp_sex, mess->all_data[j].sex);
				strcpy(mess->all_data[j].sex, mess->all_data[j + 1].sex);
				strcpy(mess->all_data[j + 1].sex, temp_sex);

				strcpy(temp_address, mess->all_data[j].address);
				strcpy(mess->all_data[j].address, mess->all_data[j + 1].address);
				strcpy(mess->all_data[j + 1].address, temp_address);
			}
		}
	}
	printf("%-8s\t%-8s\t%-8s\t%-20s\t%-20s\n", "姓名", "性别", "年龄", "联系方式", "住址");
	for (j = 0; j < mess->available_data; j++)
	{
		printf("%-8s\t%-8s\t%-8d\t%-20d\t%-20s\n",
			mess->all_data[j].name,
			mess->all_data[j].sex,
			mess->all_data[j].age,
			mess->all_data[j].tele,
			mess->all_data[j].address);
	}
}
void sort2(message* mess)
{
	int i = 0;
	int j = 0;
	int temp_age = 0;
	int temp_tele = 0;
	char temp_name[max_name] = { 0 };
	char temp_sex[max_sex] = { 0 };
	char temp_address[max_address] = { 0 };
	for (i = 0; i < mess->available_data - 1; i++)
	{
		for (j = 0; j < mess->available_data - 1 - i; j++)
		{
			if (mess->all_data[j].age < mess->all_data[j + 1].age)
			{
				temp_age = mess->all_data[j].age;//没把name改为age,导致报错
				mess->all_data[j].age = mess->all_data[j + 1].age;
				mess->all_data[j + 1].age = temp_age;

				temp_tele = mess->all_data[j].tele;//没把name改为age,导致报错
				mess->all_data[j].tele = mess->all_data[j + 1].tele;
				mess->all_data[j + 1].tele = temp_tele;

				strcpy(temp_name, mess->all_data[j].name);//不交换name，就显示只交换了年龄，其他信息未排序
				strcpy(mess->all_data[j].name, mess->all_data[j + 1].name);
				strcpy(mess->all_data[j + 1].name, temp_name);

				strcpy(temp_sex, mess->all_data[j].sex);
				strcpy(mess->all_data[j].sex, mess->all_data[j + 1].sex);
				strcpy(mess->all_data[j + 1].sex, temp_sex);

				strcpy(temp_address, mess->all_data[j].address);
				strcpy(mess->all_data[j].address, mess->all_data[j + 1].address);
				strcpy(mess->all_data[j + 1].address, temp_address);
			}
		}
	}
	printf("%-8s\t%-8s\t%-8s\t%-20s\t%-20s\n", "姓名", "性别", "年龄", "联系方式", "住址");
	for (j = 0; j < mess->available_data; j++)
	{
		printf("%-8s\t%-8s\t%-8d\t%-20d\t%-20s\n",
			mess->all_data[j].name,
			mess->all_data[j].sex,
			mess->all_data[j].age,
			mess->all_data[j].tele,
			mess->all_data[j].address);
	}
}
void sort_message(message* mess)
{
	int i = 0;
	sort_menu();
	printf("请输入你要排序的方式（年龄）:");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
		sort1(mess);//woc!!!!!!!!这里是传mess,而不是&mess，否则始终无法输出数据
		break;
	case 2:
		sort2(mess);
		break;
	default:
		break;
	}
}
//mess已经是一个指针，它存储了message结构体的地址。当你使用&mess时，你其实是在获取这个指针变量自身的地址，而不是它所指向的message结构体。
// 因此，在这种情况下，你应该直接传递mess（即地址），而不是&mess。
// 这样，sort1函数就能正确地接收到一个指向message结构体的指针，并能够操作这个结构体。
//总的来说，选择传值还是传地址取决于你是否需要在函数内部修改实参。
//如果需要修改实参，那么应该使用传地址；如果不需要修改实参或者不希望实参被修改，那么应该使用传值。
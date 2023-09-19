#include"address_book.h"

//��̬�洢
void init_message(message* mess)
{
	//mess->all_dataд��content* all_data�������޷�������Ϣ
	mess->all_data = (content*)malloc(init_cap * sizeof(content));
	if (mess->all_data == NULL)//���ǵ�Ҫ����û�ڴ��ǰ��
	{
		perror("init_message");
		return;
	}
	mess->capacity = init_cap;
	mess->available_data = 0;

	//��ȡ��Ϣ(������������add�е��ã�����ɾ����)
	fread_message(mess);//û��������ã�����ʼ���޷���ȡ���ݣ�������������������������������������������������������������
}

void fread_message(message* mess)
{
	content temp = { 0 };
	FILE* pf = fopen("C:\\Users\\�����˵�Ȧ��Ů��\\source\\repos\\Project5\\ͨѶ¼(��̬����)\\address_book.txt", "r");
	while (fread(&temp,sizeof(content),1,pf))
	{
		expend_capacity(mess);
		mess->all_data[mess->available_data] = temp;
		mess->available_data++;
	}
	fclose(pf);
	pf = NULL;
}

////��ʼ��ͨѶ¼��Ϣ
//void init_message(message* mess)
//{
//	mess->available_data = 0;
//	memset(mess->all_data, 0, sizeof(mess->all_data));//memset�ڴ�����(��ʼ����ȫ0���ȫ0)
//}

void expend_capacity(message* mess)
{
	if (mess->available_data == mess->capacity)
	{
		//(mess->capacity + add_cap)*sizeof(content)д��mess->capacity + add_cap
		content* ptr = (content*)realloc(mess->all_data, (mess->capacity + add_cap) * sizeof(content));
		if (ptr != NULL)
		{
			mess->all_data = ptr;
			mess->capacity += add_cap;
			printf("���ݳɹ���\n");
		}
		else
		{
			printf("�洢�������޷������Ϣ��\n");
		}
	}
}

//��̬����
void add_message(message* mess)
{
	//����
	expend_capacity(mess);
	if (isalnum)
	{
		printf("������������");
		scanf("%s", mess->all_data[mess->available_data].name);
		printf("�������Ա�");
		scanf("%s", mess->all_data[mess->available_data].sex);//�޷���ȡ�Ա�ԭ��scanf�м���"\n"������������
		//int i=0;scanf("%d",&i);
		//Ҫȡ��ַ
		printf("���������䣺");
		scanf("%d", &(mess->all_data[mess->available_data].age));
		printf("��������ϵ��ʽ��");
		scanf("%d", &(mess->all_data[mess->available_data].tele));
		printf("������סַ��");
		scanf("%s", mess->all_data[mess->available_data].address);

	}
	mess->available_data++;//���ÿռ�+1
	printf("������Ϣ�ɹ���\n");
}

void fwrite_message(message* mess)
{
	int i = 0;
	FILE* pf = fopen("C:\\Users\\�����˵�Ȧ��Ů��\\source\\repos\\Project5\\ͨѶ¼(��̬����)\\address_book.txt", "w");
	if (pf == NULL)
	{
		perror("fwrite_message");
		return;
	}
	for ( i = 0; i < mess->available_data; i++)
	{
		//mess->all_data+i:������+i��Ԫ�صĵ�ַ
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

////��̬�洢
//void add_message(message* mess)
//{
//	if (mess->available_data == max_person)
//	{
//		printf("ͨѶ¼������Ϣ�����������޷��������Ϣ��\n");
//		return;//����ִ�У������÷���ֵ
//	}
//	else
//	{
//		// mess->all_data[mess->available_data]�������ÿռ����Ϣ�Ž���������Ӧ�±�Ŀռ�
//		// �ѵ�n����ӽ�������Ϣ�������������±�Ϊn��λ��
//		// available=1 ==��all_data=1
//		// ������0��ѧ�������±�Ϊ0��all_data��
//		printf("������������");
//		scanf("%s", mess->all_data[mess->available_data].name);
//		printf("�������Ա�");
//		scanf("%s", mess->all_data[mess->available_data].sex);//�޷���ȡ�Ա�ԭ��scanf�м���"\n"������������
//		//int i=0;scanf("%d",&i);
//		//Ҫȡ��ַ
//		printf("���������䣺");
//		scanf("%d", &(mess->all_data[mess->available_data].age));
//		printf("��������ϵ��ʽ��");
//		scanf("%d",&(mess->all_data[mess->available_data].tele));
//		printf("������סַ��");
//		scanf("%s", mess->all_data[mess->available_data].address);
//		mess->available_data++;//���ÿռ�+1
//		printf("������Ϣ�ɹ���\n");
//	}
//}

void print_message(const message* mess)//����û�뵽Ҫ�̶�mess
{
	//��ӡ����(-�����)
	printf("%-8s\t%-8s\t%-8s\t%-20s\t%-20s\n", "����", "�Ա�", "����", "��ϵ��ʽ", "סַ");
	//��ӡ����
	int i = 0;
	for ( i = 0; i < mess->available_data; i++)
	{
		printf("%-8s\t%-8s\t%-8d\t%-20d\t%-20s\n",//���ǰ� "����", "��ϵ��ʽ"��Ϊ��%d��
			mess->all_data[i].name,//û�п��ǵ���i��������д��all_data.name
			mess->all_data[i].sex,
			mess->all_data[i].age,
			mess->all_data[i].tele,
			mess->all_data[i].address);
	}
}
//static:ֻ���ڱ�Դ�ļ��ã����ܱ�����Դ�ļ�ʹ��
//����һ���벻���ĵط�
static int find_all_names(message* mess, char name[], int ret[])
{
	int i = 0;
	int j = 0;
	for (i = 0; i < mess->available_data; i++)
	{
		//�����ַ�������ֱ���õȺţ���������
		if (strcmp(name, mess->all_data[i].name) == 0)
		{
			ret[j] = i;//������������ͬ���±�洢��һ��������
			j++;//��¼�洢��ret�����е���������
		}
	}
	return j;
}

void delete_message(message* mess)
{
	//�ж�
	if (mess->available_data == 0)
	{
		printf("ͨѶ¼Ϊ�գ��޷�ɾ����\n");
		return;
	}
	int* ret = (int*)malloc(mess->capacity * sizeof(int));
	if (ret == NULL)//��������ж�
	{
		return;
	}
	//int ret[max_person] = { 0 };//������������ͬ���±�洢��һ��������
	char name[max_name] = { 0 };//д��int���ͣ����
	printf("��������Ҫɾ����(��Ϣ)���֣�");
	//int�ĳ�char֮��%dû�ĳ�%s������������ʲô������ʾ��Ϣ�����ڣ�������
	scanf("%s", name);
	int count = find_all_names(mess, name, ret);//û���ǵ�ɾ�����޸ġ���ѯ��Ҫ�õ������ҡ�ָ��
	if (count == 0)
	{
		printf("���������Ϣ�����ڣ��޷�ɾ����\n");
		return;
	}
	//ִ��
	int i = 0;
	//count:��ͬ���ֵ�����,for����Ҫôд��count-1��i>0��Ҫôд��count��i>=0��������ôɾ�������ԣ�����
	for (i = count - 1; i >= 0; i--)
	{
		int index = ret[i];//�벻���������벻��!!!!
		while (index < mess->available_data - 1)
		{
			//available_data - 1,count - 1ԭ�����һ�������滻֮�󣬻���������һ�������±�+1������ջ���
			//����1 2 3 4 5����1ɾ����2���ǵ�1��λ�ã�3����2λ�ã�4����3��5����4���������һ�������5����Ŀ�ֵ����5�����
			mess->all_data[index] = mess->all_data[index + 1];
			index++;
		}
		mess->available_data--; //--д��++������������ôɾ����ӡ���ɻ�����
	}
	printf("ɾ���ɹ���\n");
	free(ret);//һ��ʼû�ӽ�ȥ��˽������
	ret = NULL;//��Ҳ����
}

void search_message(message* mess)
{
	char name[max_name] = { 0 };
	while (1)
	{
		printf("��������Ҫ���ҵ����֣�");
		scanf("%s", name);
		int* ret = (int*)malloc(mess->capacity * sizeof(int)); 
		if (ret == NULL)//��������ж�
		{
			return;
		}
		//int ret[max_person] = { 0 };//�벻���������벻��������������
		int count = find_all_names(mess, name, ret);
		if (count == 0)
		{
			printf("���������Ϣ�����ڣ��޷����ң�\n");
			return;
		}
		else
		{
			printf("���ҵ���Ϣ��\n");
			printf("%-8s\t%-8s\t%-8s\t%-20s\t%-20s\n", "����", "�Ա�", "����", "��ϵ��ʽ", "סַ");
			int i = 0;
			for (i = 0; i < count; i++)
			{
				printf("%-8s\t%-8s\t%-8d\t%-20d\t%-20s\n",
					mess->all_data[ret[i]].name,//ret[i]:������������ͬ���±�洢��һ��������
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
	printf("��������Ҫ�޸ĵ�����������");
	scanf("%s", name);
	int* ret = (int*)malloc(mess->capacity * sizeof(int));
	if (ret == NULL)//��������ж�
	{
		return;
	}
	//int ret[max_person] = { 0 };//�벻���������벻��������������
	int count = find_all_names(mess, name, ret);
	int i = 0;
	if (count == 0)
	{
		printf("���������Ϣ�����ڣ��޷��޸ģ�\n");
		return;
	}
	for (i = 0; i < count; i++) 
	{
		char choice = 0;
		printf("�ҵ���%d��ƥ����ˣ�������%s��ȷ���޸���Ϣ��(y/n)? ���߼����������֣�%s ���в�ѯ?\n", i + 1, mess->all_data[ret[i]].name, mess->all_data[ret[i]].name);
		scanf(" %c", &choice); //ע��ո������������������е��κοհ��ַ�(�벻���������벻����������)
		if (choice == 'y' || choice == 'Y') 
		{
			printf("������������");
			scanf("%s", mess->all_data[ret[i]].name);// ret[i]:������������ͬ���±�洢��һ��������
			printf("�������Ա�");
			scanf("%s", mess->all_data[ret[i]].sex);
			printf("���������䣺");
			scanf("%d", &(mess->all_data[ret[i]].age));
			printf("��������ϵ��ʽ��");
			scanf("%d", &(mess->all_data[ret[i]].tele));
			printf("������סַ��");
			scanf("%s", mess->all_data[ret[i]].address);
			printf("�޸���Ϣ�ɹ���\n");
			break;
		}
	}
	if (i == count)
	{
		printf("��%d�����ݣ��Ѳ�ѯ��ϣ�������ѡ��\n",count);
	}
	free(ret);
	ret = NULL;

}

void sort_menu()
{
	printf("*********************\n");
	printf("******* 1.���� ******\n");
	printf("******* 2.���� ******\n");
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
				temp_age = mess->all_data[j].age;//û��name��Ϊage,���±���
				mess->all_data[j].age = mess->all_data[j + 1].age;
				mess->all_data[j + 1].age = temp_age;

				temp_tele = mess->all_data[j].tele;//û��name��Ϊage,���±���
				mess->all_data[j].tele = mess->all_data[j + 1].tele;
				mess->all_data[j + 1].tele = temp_tele;

				strcpy(temp_name, mess->all_data[j].name);//������name������ʾֻ���������䣬������Ϣδ����
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
	printf("%-8s\t%-8s\t%-8s\t%-20s\t%-20s\n", "����", "�Ա�", "����", "��ϵ��ʽ", "סַ");
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
				temp_age = mess->all_data[j].age;//û��name��Ϊage,���±���
				mess->all_data[j].age = mess->all_data[j + 1].age;
				mess->all_data[j + 1].age = temp_age;

				temp_tele = mess->all_data[j].tele;//û��name��Ϊage,���±���
				mess->all_data[j].tele = mess->all_data[j + 1].tele;
				mess->all_data[j + 1].tele = temp_tele;

				strcpy(temp_name, mess->all_data[j].name);//������name������ʾֻ���������䣬������Ϣδ����
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
	printf("%-8s\t%-8s\t%-8s\t%-20s\t%-20s\n", "����", "�Ա�", "����", "��ϵ��ʽ", "סַ");
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
	printf("��������Ҫ����ķ�ʽ�����䣩:");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
		sort1(mess);//woc!!!!!!!!�����Ǵ�mess,������&mess������ʼ���޷��������
		break;
	case 2:
		sort2(mess);
		break;
	default:
		break;
	}
}
//mess�Ѿ���һ��ָ�룬���洢��message�ṹ��ĵ�ַ������ʹ��&messʱ������ʵ���ڻ�ȡ���ָ���������ĵ�ַ������������ָ���message�ṹ�塣
// ��ˣ�����������£���Ӧ��ֱ�Ӵ���mess������ַ����������&mess��
// ������sort1����������ȷ�ؽ��յ�һ��ָ��message�ṹ���ָ�룬���ܹ���������ṹ�塣
//�ܵ���˵��ѡ��ֵ���Ǵ���ַȡ�������Ƿ���Ҫ�ں����ڲ��޸�ʵ�Ρ�
//�����Ҫ�޸�ʵ�Σ���ôӦ��ʹ�ô���ַ���������Ҫ�޸�ʵ�λ��߲�ϣ��ʵ�α��޸ģ���ôӦ��ʹ�ô�ֵ��
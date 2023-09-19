#include"address_book.h"

void menu()
{
	printf("\n  ********************************************\n");
	printf("  ********************************************\n");
	printf("  ******    ͨ   Ѷ   ¼   ϵ   ͳ     *******\n");
	printf("  ******    0.�˳�ϵͳ     1.������Ϣ  *******\n");
	printf("  ******    2.ɾ����Ϣ     3.������Ϣ  *******\n");
	printf("  ******    4.�޸���Ϣ     5.������Ϣ  *******\n");
	printf("  ******    6.��ӡ��Ϣ     7.������Ϣ  *******\n");
	printf("  ********************************************\n");
	printf("  ********************************************\n");
}

enum option
{
	EXIT,
	ADD,
	DELETE,
	SEARCH,
	MODIFY,
	SORT,
	PRINT,
	SAVE
};
int main()
{
	//����ͨѶ¼
	message mess;
	//��ʼ��ͨѶ¼(&mess����mess�� * mess������ַ�����Ǵ�ֵ)
	init_message(&mess);
	int input = 0;
	if (isdigit)
	{
		do
		{
			menu();
			printf("���������ѡ��: ");
			scanf("%d", &input);
			switch (input)
			{
			case EXIT:
				printf("�˳�ϵͳ!\n");
				//�ڴ��ͷ�/����
				release_message(&mess);
				break;
			case ADD:
				printf("������Ϣ:\n");
				add_message(&mess);
				break;
			case DELETE:
				printf("ɾ����Ϣ:\n");
				delete_message(&mess);
				break;
			case SEARCH:
				printf("������Ϣ:\n");
				search_message(&mess);
				break;
			case MODIFY:
				printf("�޸���Ϣ:\n");
				modify_message(&mess);
				break;
			case SORT:
				printf("������Ϣ:\n");
				sort_message(&mess);
				break;
			case PRINT:
				printf("��ӡ��Ϣ��\n");
				print_message(&mess);
				break;
			case SAVE:
				//����д��
				fwrite_message(&mess);
				printf("������Ϣ�ɹ���\n");
				break;
			default:
				printf("�޸�ѡ����������룡\n");
				break;
			}
		} while (input);
	}
	return 0;
}
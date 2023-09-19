#include"address_book.h"

void menu()
{
	printf("\n  ********************************************\n");
	printf("  ********************************************\n");
	printf("  ******    通   讯   录   系   统     *******\n");
	printf("  ******    0.退出系统     1.增加信息  *******\n");
	printf("  ******    2.删除信息     3.查找信息  *******\n");
	printf("  ******    4.修改信息     5.排序信息  *******\n");
	printf("  ******    6.打印信息     7.保存信息  *******\n");
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
	//创建通讯录
	message mess;
	//初始化通讯录(&mess不是mess或 * mess；传地址而不是传值)
	init_message(&mess);
	int input = 0;
	if (isdigit)
	{
		do
		{
			menu();
			printf("请输入你的选择: ");
			scanf("%d", &input);
			switch (input)
			{
			case EXIT:
				printf("退出系统!\n");
				//内存释放/回收
				release_message(&mess);
				break;
			case ADD:
				printf("增加信息:\n");
				add_message(&mess);
				break;
			case DELETE:
				printf("删除信息:\n");
				delete_message(&mess);
				break;
			case SEARCH:
				printf("查找信息:\n");
				search_message(&mess);
				break;
			case MODIFY:
				printf("修改信息:\n");
				modify_message(&mess);
				break;
			case SORT:
				printf("排序信息:\n");
				sort_message(&mess);
				break;
			case PRINT:
				printf("打印信息：\n");
				print_message(&mess);
				break;
			case SAVE:
				//数据写入
				fwrite_message(&mess);
				printf("保存信息成功！\n");
				break;
			default:
				printf("无该选项，请重新输入！\n");
				break;
			}
		} while (input);
	}
	return 0;
}
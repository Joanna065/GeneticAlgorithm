#include "CMenuTree.h"
#include "CManager.h"

using namespace std;

int main()
{
	CManager* pc_manager = new CManager();
	CMenuTree* pc_init_menu_object = new CMenuTree();
	pc_init_menu_object->vInitMenuItems(pc_manager);
	pc_init_menu_object->vRunMenu();
	
	delete pc_init_menu_object;
	delete pc_manager;

	//vector<bool> v_genotype1{ 1, 1, 0, 1 };
	//vector <bool > v_genotype2{ 0, 1, 0 ,0 };
	//CIndividual<bool> pcInd_1 = new CIndividual<bool>(v_genotype1);

	//system("Pause");
	return 0;
}

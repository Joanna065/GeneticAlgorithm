#include "CGeneticAlgorithm.h"
#include <random>
#include <iostream>
#include <time.h>
#include "ConstansAlgorithm.h"
#include <string>
using namespace std;

//	individual class
template<class T>
CIndividual<T>::CIndividual()
{
}

template<class T>
CIndividual<T>::CIndividual(vector<T>& piGenotype, double dMutProb, std::mt19937& cRandEngine)
	: pi_genotype(piGenotype), c_rand_engine(cRandEngine), d_mutation_probability(dMutProb)
{
	//random_device c_seed_generator;				// Will be used to obtain a seed for the random number engine
	//c_rand_engine.seed(c_seed_generator());		// //Standard mersenne_twister_engine seeded with rd()
}

template<class T>
CIndividual<T>::CIndividual(CIndividual<T>& pcOther)
	: pi_genotype(pcOther.pi_genotype), c_rand_engine(pcOther.c_rand_engine), d_mutation_probability(pcOther.d_mutation_probability)
{
}

template<class T>
CIndividual<T>::~CIndividual()
{
	pi_genotype.clear();
}

template<class T>
double CIndividual<T>::dFitnessCalculate(CProblem<T>* pcProblem)
{
	return pcProblem->dCalculateSolution(pi_genotype);
}

void CIndividual<bool>::v_mutate()
{
	uniform_real_distribution<double> double_chooser(0.0, 1.0);
	double d_mut_prob = 0;

	for (int ii = 0; ii < int(pi_genotype.size()); ii++)
	{
		d_mut_prob = double_chooser(c_rand_engine);
		if (d_mut_prob <= d_mutation_probability)
		{
			pi_genotype[ii] = !pi_genotype[ii];
		}
	}
}

void CIndividual<int>::v_mutate()
{
	uniform_real_distribution<double> double_chooser(0.0, 1.0);
	double d_mut_prob = 0;

	for (int ii = 0; ii < int(pi_genotype.size()); ii++)
	{
		d_mut_prob = double_chooser(c_rand_engine);
		if (d_mut_prob <= d_mutation_probability)
		{
			pi_genotype[ii] = MAX_INTEGER_ITEM_TO_TAKE - pi_genotype[ii];
		}
	}
}

void CIndividual<double>::v_mutate()
{
	uniform_real_distribution<double> double_chooser(0.0, 1.0);
	double d_mut_prob = 0;

	for (int ii = 0; ii < int(pi_genotype.size()); ii++)
	{
		d_mut_prob = double_chooser(c_rand_engine);
		if (d_mut_prob <= d_mutation_probability)
		{
			pi_genotype[ii] = MAX_DOUBLE_ITEM_TO_TAKE - pi_genotype[ii];
		}
	}
}

template<class T>
CIndividual<T>& CIndividual<T>::v_cross_over(CIndividual<T>& pcOther)
{
	vector<T> v_child_genotype;
	v_child_genotype.reserve(pi_genotype.size());
	CIndividual<T>* pc_child =  new CIndividual<T>(v_child_genotype, d_mutation_probability, c_rand_engine);

	uniform_int_distribution<int> cross_point_chooser(1, pi_genotype.size() - 1);
	int i_cross_point = cross_point_chooser(c_rand_engine);

	//memcpy(pc_child->pi_genotype.data(), this->pi_genotype.data(), i_cross_point * sizeof(int));
	//memcpy(pc_child->pi_genotype.data() + i_cross_point, pcOther.pi_genotype.data() + i_cross_point, (pi_genotype.size() - i_cross_point) * sizeof(int));

	for(int i = 0; i < i_cross_point; i++)
	{
		pc_child->pi_genotype.push_back(this->pi_genotype[i]);
	}
	for(int ii = i_cross_point; ii < int(pi_genotype.size()); ii++)
	{
		pc_child->pi_genotype.push_back(pcOther.pi_genotype[ii]);
	}
	return *pc_child;
}

template <class T>
CIndividual<T>& CIndividual<T>::operator=(const CIndividual<T>& pcOther)
{
	c_rand_engine = pcOther.c_rand_engine;
	d_mutation_probability = pcOther.d_mutation_probability;
	for (int ii = 0; ii < int(pcOther.pi_genotype.size()); ii++)
	{
		pi_genotype.push_back(pcOther.pi_genotype[ii]);
	}
	return *this;
}

template <class T>
CIndividual<T>& CIndividual<T>::operator^(CIndividual<T>& pcOther)
{
	vector<T> v_child_genotype;
	v_child_genotype.reserve(pi_genotype.size());
	CIndividual<T>* pc_child = new CIndividual<T>(v_child_genotype, d_mutation_probability, c_rand_engine);

	for (int i = 0; i < int(pi_genotype.size()); i++)
	{
		pc_child->pi_genotype.push_back((this->pi_genotype[i] + pcOther.pi_genotype[i])/2);
	}
	return *pc_child;
}

CIndividual<bool>& CIndividual<bool>::operator^(CIndividual<bool>& pcOther)
{
	vector<bool> v_child_genotype;
	v_child_genotype.reserve(pi_genotype.size());
	CIndividual<bool>* pc_child = new CIndividual<bool>(v_child_genotype, d_mutation_probability, c_rand_engine);

	for (int i = 0; i < int(pi_genotype.size()); i++)
	{
		pc_child->pi_genotype.push_back(this->pi_genotype[i] ^ pcOther.pi_genotype[i]);
	}
	return *pc_child;
}

template <class T>
CIndividual<T>& CIndividual<T>::operator++(int)	//mutation operator
{
	this->v_mutate();
	return *this;		// no memory leak because of returning yourself !!
}

template <class T>
CIndividual<T>& CIndividual<T>::operator+(CIndividual<T>& pcOtherParent)	//crossover operator
{
	return this->v_cross_over(pcOtherParent);
}

template <class T>
std::string CIndividual<T>::sToString()
{
	string return_string = "";
	for (int i = 0; i < int(pi_genotype.size()); i++) {
		return_string = return_string + to_string(pi_genotype[i]) + " ";
	}
	return return_string;
}

//	--------  genetic algorithm class  -----------
template<class T>
CGeneticAlgorithm<T>::CGeneticAlgorithm()
{
	pc_problem = nullptr;
	i_time = 0;
	i_population_size = 0;
	d_cross_probability = 0;
	d_mutation_probability = 0;
	d_best_fitness = 0;
	d_best_fitness_2 = 0;
	random_device c_seed_generator;				// Will be used to obtain a seed for the random number engine
	c_rand_engine.seed(c_seed_generator());		// //Standard mersenne_twister_engine seeded with rd()
	pc_current_best = nullptr;
	pc_current_best_2 = nullptr;
}

template<class T>
CGeneticAlgorithm<T>::CGeneticAlgorithm(int iPopulationSize, double fCrossProb, double fMutationProb, int iTimeInSec, CProblem<T>* pcProblem)
	: pc_problem(pcProblem), i_time(iTimeInSec), i_population_size(iPopulationSize),
	d_cross_probability(fCrossProb), d_mutation_probability(fMutationProb)
{
	d_best_fitness = 0;
	d_best_fitness_2 = 0;
	random_device c_seed_generator;				// Will be used to obtain a seed for the random number engine
	c_rand_engine.seed(c_seed_generator());		// //Standard mersenne_twister_engine seeded with rd()
	pc_current_best = nullptr;
	pc_current_best_2 = nullptr;
}

template<class T>
CGeneticAlgorithm<T>::~CGeneticAlgorithm()
{
	if(!vc_population.empty()) v_delete_population(vc_population);
	delete pc_problem;
	delete pc_current_best;
	delete pc_current_best_2;
}

template<class T>
bool CGeneticAlgorithm<T>::bLoadData(int iPopulationSize, double dCrossProb, double dMutationProb, int iTimeInSec, CProblem<T>* pcProblem, string& sError)
{
	if (iPopulationSize <= 0) {
		sError = ERROR_POPULATION_SIZE;
		return false;
	}
	if (dCrossProb < 0 || dMutationProb < 0 || dCrossProb > 1 || dMutationProb > 1) {
		sError = ERROR_PARAMETERS_FOR_MUT_CROSS;
		return false;
	}
	if (iTimeInSec < 0) {
		sError = ERROR_ITER_TIME;
		return false;
	}
	if (pcProblem == nullptr) {
		sError = ERROR_NULLPTR_PROBLEM;
		return false;
	}
	return true;
}

template<class T>
void CGeneticAlgorithm<T>::vSetProblem(CProblem<T>* pcProblem)
{
	delete pc_problem;
	pc_problem = pcProblem;
	v_delete_population(vc_population);
	delete pc_current_best;
	delete pc_current_best_2;
	d_best_fitness = 0;
	d_best_fitness_2 = 0;
}

template<class T>
void CGeneticAlgorithm<T>::vRun()
{
	const time_t t_start_time = time(nullptr);
	time_t t_current_time = 0;
	
	v_init_population(); // generate random population

	v_init_current_bests(vc_population[0], vc_population[1]);	//set example best solution

	for (int i = 2; i < int(vc_population.size()); i++) {
		if (d_best_fitness < vc_population[i]->dFitnessCalculate(pc_problem)) {
		
			v_update_bests(vc_population[i]);
		}
	}

	while (t_current_time - t_start_time < i_time)
	{
		// creates empty new population
		vector <CIndividual<T>*> v_new_population;

		//add mutated bests to new population
		CIndividual<T>* pc_best1 = new CIndividual<T>(*pc_current_best);
		CIndividual<T>* pc_best2 = new CIndividual<T>(*pc_current_best_2);
		(*pc_best1)++;
		(*pc_best2)++;
		v_new_population.push_back(pc_best1);
		v_new_population.push_back(pc_best2);

		// until new population has the same size like old one
		for (int iter = 0; iter < i_population_size - 2; iter++)
		{
			// crossing over
			CIndividual<T>* pc_child = v_select_parents_and_cross_over();
			//mutation
			(*pc_child)++;

			//add mutated individual
			v_update_bests(pc_child);
			v_new_population.push_back(pc_child);
		}
		v_delete_population(vc_population);	// deletes old population
		vc_population = v_new_population;	// replaces old population with new one

		t_current_time = time(nullptr);
	}
}

template <class T>
std::string CGeneticAlgorithm<T>::sBestSolution()
{
	return BEST_SOLUTION + pc_current_best->sToString() + "  " + VALUE +  to_string(pc_current_best->dFitnessCalculate(pc_problem));
}

template<class T>
void CGeneticAlgorithm<T>::v_init_current_bests(CIndividual<T>* pcCurrentBest, CIndividual<T>* pcCurrentBest2)
{
	if (pc_current_best != nullptr) delete pc_current_best;
	if (pc_current_best_2 != nullptr) delete pc_current_best_2;

	if(pcCurrentBest->dFitnessCalculate(pc_problem) >= pcCurrentBest2->dFitnessCalculate(pc_problem))
	{
		// first
		pc_current_best = new CIndividual<T>(*pcCurrentBest);
		d_best_fitness = pc_current_best->dFitnessCalculate(pc_problem);
		// second
		pc_current_best_2 = new CIndividual<T>(*pcCurrentBest2);
		d_best_fitness_2 = pc_current_best_2->dFitnessCalculate(pc_problem);

	}else
	{
		pc_current_best = new CIndividual<T>(*pcCurrentBest2);
		d_best_fitness = pc_current_best->dFitnessCalculate(pc_problem);

		pc_current_best_2 = new CIndividual<T>(*pcCurrentBest);
		d_best_fitness_2 = pc_current_best_2->dFitnessCalculate(pc_problem);
	}
}

template<class T>
void CGeneticAlgorithm<T>::v_update_bests(CIndividual<T>* pcIndividual)
{
	if(pcIndividual->dFitnessCalculate(pc_problem) > d_best_fitness)
	{
		delete pc_current_best_2;
		pc_current_best_2 = new CIndividual<T>(*pc_current_best);	//set best as second best
		d_best_fitness_2 = pc_current_best_2->dFitnessCalculate(pc_problem);

		delete pc_current_best;
		pc_current_best = new CIndividual<T>(*pcIndividual);	// set new individual as best
		d_best_fitness = pc_current_best->dFitnessCalculate(pc_problem);
	}else if(pcIndividual->dFitnessCalculate(pc_problem) > d_best_fitness_2)
	{
		delete pc_current_best_2;
		pc_current_best_2 = new CIndividual<T>(*pcIndividual);
		d_best_fitness_2 = pc_current_best_2->dFitnessCalculate(pc_problem);
	}
}

// init start population - randomly distribute 0/1 in vector of integers (genotype for CIndividual)
void CGeneticAlgorithm<bool>::v_init_population()
{
	if (!vc_population.empty()) v_delete_population(vc_population);

	uniform_int_distribution<int> bool_distrubition(0, 1);

	for(int i = 0; i < i_population_size; i ++)
	{
		vector<bool> vb_rand_genotype(pc_problem->iGetSolutionLength());
		
		for(int ii = 0; ii < int(vb_rand_genotype.size()); ii++)
		{
			vb_rand_genotype[ii] = bool_distrubition(c_rand_engine);
		}

		CIndividual<bool>* pc_rand_individual = new CIndividual<bool>(vb_rand_genotype, d_mutation_probability, c_rand_engine);
		vc_population.push_back(pc_rand_individual);
	}
}

void CGeneticAlgorithm<int>::v_init_population()
{
	if(!vc_population.empty()) v_delete_population(vc_population);	// in case population vector is not empty (but it should be)

	uniform_int_distribution<int> int_distrubition(0, MAX_INTEGER_ITEM_TO_TAKE);

	for (int i = 0; i < i_population_size; i++)
	{
		vector<int> vi_rand_genotype(pc_problem->iGetSolutionLength());

		for (int ii = 0; ii < int(vi_rand_genotype.size()); ii++)
		{
			vi_rand_genotype[ii] = int_distrubition(c_rand_engine);
		}

		CIndividual<int>* pc_rand_individual = new CIndividual<int>(vi_rand_genotype, d_mutation_probability, c_rand_engine);
		vc_population.push_back(pc_rand_individual);
	}
}

void CGeneticAlgorithm<double>::v_init_population()
{
	if (!vc_population.empty()) v_delete_population(vc_population);

	uniform_real_distribution<double> double_distrubition(0, MAX_DOUBLE_ITEM_TO_TAKE);

	for (int i = 0; i < i_population_size; i++)
	{
		vector<double> vd_rand_genotype(pc_problem->iGetSolutionLength());

		for (int ii = 0; ii < int(vd_rand_genotype.size()); ii++)
		{
			vd_rand_genotype[ii] = double_distrubition(c_rand_engine);
		}
		CIndividual<double>* pc_rand_individual = new CIndividual<double>(vd_rand_genotype, d_mutation_probability, c_rand_engine);
		vc_population.push_back(pc_rand_individual);
	}
}

template<class T>
void CGeneticAlgorithm<T>::v_select_parent(CIndividual<T>** pcParent)
{
	uniform_int_distribution<int> int_chooser(0, i_population_size - 1);

	CIndividual<T>* pc_select_first = vc_population[int_chooser(c_rand_engine)];
	CIndividual<T>* pc_select_second = vc_population[int_chooser(c_rand_engine)];

	if (pc_select_first->dFitnessCalculate(pc_problem) >= pc_select_second->dFitnessCalculate(pc_problem))
	{
		*pcParent = new CIndividual<T>(*pc_select_first);
	}
	else
	{
		*pcParent = new CIndividual<T>(*pc_select_second);
	}
}

template<class T>
CIndividual<T>* CGeneticAlgorithm<T>::v_select_parents_and_cross_over()
{
	CIndividual<T>* pc_mom = nullptr;
	CIndividual<T>* pc_dad = nullptr;
	v_select_parent(&pc_mom);
	v_select_parent(&pc_dad);
	CIndividual<T>* pc_child = nullptr;

	uniform_real_distribution<double> double_chooser(0.0, 1.0);

	if (double_chooser(c_rand_engine) <= d_cross_probability)
	{
		pc_child = &(*pc_mom + *pc_dad);
		delete pc_mom;
		delete pc_dad;
	}
	else
	{
		pc_child = new CIndividual<T>(*pc_mom);
		delete pc_mom;
		delete pc_dad;
	}
	return pc_child;
}

template<class T>
void CGeneticAlgorithm<T>::v_delete_population(vector<CIndividual<T>*>& v_pop_to_delete) const
{
	for(int i = 0; i < i_population_size; i++)
	{
		delete v_pop_to_delete[i];
	}
	v_pop_to_delete.clear();
}

template class CIndividual<bool>;
template class CIndividual<int>;
template class CIndividual<double>;
template class CGeneticAlgorithm<bool>;
template class CGeneticAlgorithm<int>;
template class CGeneticAlgorithm<double>;
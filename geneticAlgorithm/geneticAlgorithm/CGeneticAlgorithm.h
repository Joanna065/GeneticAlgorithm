#pragma once
#include <vector>
#include "CProblem.h"
#include <random>

template<class T>
class CIndividual
{
public:
	CIndividual();
	CIndividual(std::vector<T>& piGenotype, double dMutProb, std::mt19937& cRandEngine);
	CIndividual(CIndividual &pcOther);
	~CIndividual();

	double dFitnessCalculate(CProblem<T>* pcProblem);
	std::vector<T> iGetGenotype() const { return pi_genotype; }
	CIndividual<T>& operator=(const CIndividual<T>& pcOther);
	CIndividual<T>& operator^(CIndividual<T>& pcOther);
	CIndividual<T>& operator++(int);
	CIndividual<T>& operator+(CIndividual<T>& pcOtherParent);

	std::string sToString();

private:
	void v_mutate();
	CIndividual<T>& v_cross_over(CIndividual<T>& pcOther);

	std::vector<T> pi_genotype;
	std::mt19937 c_rand_engine;
	double d_mutation_probability;	// mutation probability	
};

template<class T>
class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm();
	CGeneticAlgorithm(int iPopulationSize, double dCrossProb, double dMutationProb, int iTimeInSec, CProblem<T>* pcProblem);
	~CGeneticAlgorithm();

	static bool bLoadData(int iPopulationSize, double dCrossProb, double dMutationProb, int iTimeInSec, CProblem<T>* pcProblem, std::string& sError);
	CIndividual<T>* cTakeBestSolution() { return pc_current_best; }
	void vSetProblem(CProblem<T>* pcProblem);
	void vRun();
	std::string sBestSolution();

private:
	void v_init_current_bests(CIndividual<T>* pcCurrentBest, CIndividual<T>* pcCurrentBest2);
	void v_update_bests(CIndividual<T>* pcIndividual);
	void v_init_population();
	void v_select_parent(CIndividual<T>** pcParent);
	CIndividual<T>* v_select_parents_and_cross_over();
	void v_delete_population(std::vector<CIndividual<T>*>&) const;

	CProblem<T>* pc_problem;
	CIndividual<T>* pc_current_best;
	CIndividual<T>* pc_current_best_2;
	double d_best_fitness;
	double d_best_fitness_2;
	std::vector<CIndividual<T>*> vc_population;
	std::mt19937 c_rand_engine;

	int i_time; // end criteria
	int i_population_size;	// size of population
	double d_cross_probability; //cross over probability
	double d_mutation_probability;	// mutation probability
};






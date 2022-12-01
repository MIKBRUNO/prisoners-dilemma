#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <string>

namespace PrisonersDilemma {

	enum class Decision {
		COOPERATE,
		DEFECT
	};
	std::ostream& operator<<(std::ostream& o, Decision d);

	class Strategy {
	public:
		virtual Decision decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2) = 0;
		virtual const char* name() const = 0;
		virtual Strategy* clone() const = 0;
		inline virtual ~Strategy() {}
	};

	class CooperateStrategy : public Strategy {
	public:
		virtual Decision decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2);
		inline virtual const char* name() const { return "cooperate"; };
		inline virtual Strategy* clone() const { return new CooperateStrategy; };
		inline virtual ~CooperateStrategy() {}
	};

	class AlternatingStrategy : public Strategy {
	public:
		virtual Decision decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2);
		inline virtual const char* name() const { return "alter"; };
		inline virtual Strategy* clone() const { return new AlternatingStrategy(*this); };
		inline virtual ~AlternatingStrategy() {}
	private:
		Decision d = Decision::COOPERATE;
	};

	class GoByMajorityStrategy : public Strategy {
	public:
		virtual Decision decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2);
		inline virtual const char* name() const { return "majority"; };
		inline virtual Strategy* clone() const { return new GoByMajorityStrategy; };
		inline virtual ~GoByMajorityStrategy() {}
	};

	class VotingStrategy : public Strategy {
	public:
		explicit VotingStrategy(const std::string&);
		VotingStrategy(const VotingStrategy&);
		virtual ~VotingStrategy();
		virtual Decision decide(
			const std::vector<Decision>& myhist,
			const std::vector<Decision>& hist1,
			const std::vector<Decision>& hist2);
		inline virtual const char* name() const { return "voting"; };
		inline virtual Strategy* clone() const { return new VotingStrategy(*this); };
	private:
		std::vector<Strategy*> advisers;
	};

	// class TitForTat : public Strategy {
	// public:
	// 	explicit TitForTat(const std::string&);
	// 	TitForTat(const TitForTat&);
	// 	virtual ~TitForTat();
	// 	virtual Decision decide(
	// 		const std::vector<Decision>& myhist,
	// 		const std::vector<Decision>& hist1,
	// 		const std::vector<Decision>& hist2);
	// 	inline virtual const char* name() const { return "tit-for-tat"; };
	// 	inline virtual Strategy* clone() const { return new TitForTat(*this); };
	// private:
	// 	std::vector<Strategy*> advisers;
	// };

}
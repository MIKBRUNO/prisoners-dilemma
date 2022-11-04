#include <vector>
#include <array>
#include <string>

namespace PrisonersDilemma {

	enum class Decision {
		COOPERATE,
		DEFECT
	};

	using roundDecisions = std::vector<Decision>;

	class Strategy {
	public:
		virtual Decision decide() = 0;
	};

	class Game {
	public:
		Game(std::array<std::string, 3>&);
		Game(std::array<Strategy, 3>&);
		const roundDecisions& playRound();
		void fastPlay(unsigned int roundCount);
		const std::vector<roundDecisions>& getHistory() const;
	protected:
		std::vector<roundDecisions>* roundHistory;
		std::array<Strategy, 3>* competitors;
		
	};

}

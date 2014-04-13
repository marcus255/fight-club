#ifndef _ENGINE_H
#define _ENGINE_H

#include <QMap>
#include <QSet>
#include <QStringList>
#include <QString>

class Player;
class PlayerListener;
class GameRules;

class Engine : public QObject
{
Q_OBJECT

public:
	enum MoveResult
	{
		ValidMove,
		InvalidMove,
		FinishingMove
	};
	Engine(GameRules *rules = NULL);

	Player *loadExternalPlayer(int id);

	bool registerPlayer(Player *player);
	void unregisterPlayer(Player *player);
	void registerPlayerListener(PlayerListener *listener);
	void unregisterPlayerListener(PlayerListener *listener);

	void sendToPlayer(int id, QString msg);

	int getNextPlayer(int player);

protected:
	QStringList getPlayerParams(int id);

private slots:
	void receiveFromPlayer(int id, QString msg);
	void onPlayerLeave(int id);

private:
	void stop();
	void forwardMove(int id, QString move);
	void printStats();

	GameRules *rules;
	QMap<int, Player*> players;
	QSet<PlayerListener*> listeners;
};

#endif
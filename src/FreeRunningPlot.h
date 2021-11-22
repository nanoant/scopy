#ifndef FREERUNNINGPLOT_H
#define FREERUNNINGPLOT_H

/*Qwt includes*/
#include <qwt_plot.h>
#include <qwt_plot_renderer.h>
#include <qwt_legend.h>

/*Qt includes*/
#include <QObject>
#include <QTimer>

namespace adiscope {

class FreeRunningPlot : public QwtPlot
{
	Q_OBJECT
public:
	FreeRunningPlot(QWidget* parent);

public Q_SLOTS:
	void start();
	void startStop(bool en = true);
	void stop();
	bool isStarted();

	void setRefreshRate(double hz);
	double getRefreshRate();

	void drawPlot();
	void replot() override;

protected:
	QTimer refreshTimer;
private:
	bool started;
	double refreshRate;
	int id = 0;

};

}

#endif // FREERUNNINGPLOT_H

#include "FreeRunningPlot.h"
#include <QDebug>

namespace adiscope {
static int idHelper = 0;
FreeRunningPlot::FreeRunningPlot(QWidget* parent) : QwtPlot(parent), started(false), refreshRate(60)
{
	qDebug()<<QString::number(id)<<"Created freerunning plot";
	id = idHelper;
	idHelper++;

	connect(&refreshTimer,SIGNAL(timeout()),this,SLOT(drawPlot()));
	QwtPlotCanvas *plotCanvas = qobject_cast<QwtPlotCanvas *>( canvas() );
	//plotCanvas->setPaintAttribute(QwtPlotCanvas::BackingStore );
	plotCanvas->setPaintAttribute(QwtPlotCanvas::ImmediatePaint, false);	
	//plotCanvas->setPaintAttribute(QwtPlotCanvas::OpenGLBuffer );
	drawPlot();
}

void FreeRunningPlot::start() {
	qDebug()<<QString::number(id)<<"Starting freerunning plot";
	started = true;
	refreshTimer.setSingleShot(false);
	qDebug()<<refreshTimer.interval();
	qDebug()<<1000.0/refreshRate;
	refreshTimer.start(1000.0/refreshRate);

}

void FreeRunningPlot::startStop(bool en) {
	if(en) {
		start();
	} else  {
		stop();
	}
}

bool FreeRunningPlot::isStarted() {
	return started;
}
void FreeRunningPlot::stop() {
	qDebug()<<QString::number(id)<<"FreeRunningPlot - Stopping freerunning plot - will force one replot";
	started = false;
	refreshTimer.stop();
	drawPlot();
}
void FreeRunningPlot::setRefreshRate(double hz) {
	refreshRate = hz;
	if(refreshTimer.isActive())	{
		refreshTimer.start(1000.0/refreshRate);
	}
}

double FreeRunningPlot::getRefreshRate() {
	return refreshRate;

}
void FreeRunningPlot::drawPlot() {
	qDebug()<<QString::number(id)<<" - FreeRunningPlot - drawing plot";
	refreshTimer.setSingleShot(false);
	QwtPlot::replot();
}


void FreeRunningPlot::replot() {
	bool singleShot = refreshTimer.isSingleShot();
	if(!started && !singleShot) {
		// not started - schedule a plot next frame
		qDebug()<<QString::number(id)<<"FreeRunningPlot - freerunning plot not started - schedule next frame";
		refreshTimer.setSingleShot(true);
		refreshTimer.start(1000.0/refreshRate);
	} else {
		//qDebug()<<QString::number(id)<<"FreeRunningPlot - freerunning already started - updating axes";
	//	qDebug()<<QString::number(id)<<"FreeRunningPlot - freerunning already started";
		//QwtPlot::replot();
		//refreshTimer.setSingleShot(false);
	}
}

} // adiscope

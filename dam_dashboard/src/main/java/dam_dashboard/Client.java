package dam_dashboard;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.util.concurrent.TimeUnit;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.axis.DateTickUnit;
import org.jfree.chart.axis.DateTickUnitType;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.NumberTickUnit;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import io.vertx.core.Vertx;
import io.vertx.core.json.Json;
import io.vertx.core.json.JsonArray;
import io.vertx.ext.web.client.WebClient;

public class Client extends JFrame {
	
	private static final long serialVersionUID = 3672498792400844882L;
	private JPanel labelPanel;
	private JPanel mainPanel;
	private JLabel stateLabel;
	private JLabel manualLabel;
	private JLabel spanLabel;
	private JLabel titleLabel;
	private ChartPanel chartPanel;
	private XYSeriesCollection dataset;
	private WebClient client;
	private String host;
	private int port;
	
	public Client(String title, String host) {
		super(title);
		this.dataset = new XYSeriesCollection();
		this.mainPanel = new JPanel(new BorderLayout());
	    this.labelPanel = new JPanel();
	    this.stateLabel = new JLabel("Stato: NORMAL");
	    this.manualLabel = new JLabel("");
	    this.spanLabel = new JLabel("");
	    this.titleLabel = new JLabel(title, SwingConstants.CENTER);
	    this.initClient(host);
		
		JFreeChart chart = ChartFactory.createXYLineChart(
		        "",
		        "Tempo",
		        "Livello dell'acqua",
		        this.dataset,
		        PlotOrientation.VERTICAL,
		        true, true, false);
		
		XYPlot xyPlot = (XYPlot) chart.getPlot();
	    NumberAxis domain = (NumberAxis) xyPlot.getRangeAxis();
	    domain.setRange(3.00, 5.00);
	    domain.setTickUnit(new NumberTickUnit(0.1));
	    xyPlot.setDomainAxis(new DateAxis());
		
	    this.chartPanel = new ChartPanel(chart);
	    this.initUI();
	    this.chartPanel.setVisible(false);

	    this.mainPanel.add(this.chartPanel);
	    this.add(this.mainPanel);
	    this.setSize(1000, 1000);
	    this.pack();
	    this.setVisible(true);
	}
	
	void initUI() {
	    this.labelPanel.setLayout(new BoxLayout(this.labelPanel, BoxLayout.Y_AXIS));
	    this.stateLabel.setFont(new Font(this.stateLabel.getFont().getName(), Font.PLAIN, 20));
	    this.manualLabel.setFont(new Font(this.manualLabel.getFont().getName(), Font.PLAIN, 20));
	    this.spanLabel.setFont(new Font(this.spanLabel.getFont().getName(), Font.PLAIN, 20));
	    this.titleLabel.setFont(new Font(titleLabel.getFont().getName(), Font.PLAIN, 40));
	    this.titleLabel.setForeground(new Color(0xFF0000));
	    
	    this.labelPanel.add(Box.createRigidArea(new Dimension(5, 100)));
	    this.labelPanel.add(stateLabel);
	    this.labelPanel.add(Box.createRigidArea(new Dimension(5, 50)));
	    this.labelPanel.add(manualLabel);
	    this.labelPanel.add(Box.createRigidArea(new Dimension(5, 50)));
	    this.labelPanel.add(spanLabel);
	    this.labelPanel.setBorder(new EmptyBorder(50, 50, 50, 50));
	    
	    this.mainPanel.setBorder(new EmptyBorder(20, 20, 20, 20));
	    this.mainPanel.add(titleLabel, BorderLayout.PAGE_START);
	    this.mainPanel.add(labelPanel, BorderLayout.LINE_START);
	    this.mainPanel.add(chartPanel, BorderLayout.LINE_END);
	    
	    this.pack();
	}
	
	private void initClient(String host) {
		this.host = host;
		this.port = 80;

		Vertx vertx = Vertx.vertx();
		vertx.setPeriodic(1000, h -> {
			this.sendGet();
		});

		this.client = WebClient.create(vertx);
		this.sendGet();
	}

	private void sendGet() {
		this.client.get(port, host, "/api/data")
				   .send()
				   .onSuccess(res -> { 
					   JsonArray response = res.bodyAsJsonArray();
					   this.handleData(response);
				   })
				   .onFailure(err -> System.out.println("Something went wrong " + err.getMessage()));
	}
	
	private void updateUI(Data data) {
		this.stateLabel.setText("Stato: " + data.getState().toString());
	    if(data.isManual()) {
	    	this.manualLabel.setText("La diga si trova in modalità manuale");
	    	this.manualLabel.setVisible(true);
	    } else {
	    	this.manualLabel.setVisible(false);
	    	//System.out.println(data.toString());
	    }
	    
	    switch(data.getState()) {
		    case NORMAL:
		    	this.chartPanel.setVisible(false);
		    	this.spanLabel.setVisible(false);
		    	break;
		    case PRE_ALARM:
		    	this.chartPanel.setVisible(true);
		    	this.spanLabel.setVisible(false);
		    	break;
		    case ALARM:
		    	this.chartPanel.setVisible(true);
		    	this.spanLabel.setVisible(true);
		    	this.spanLabel.setText("Apertura diga: " + data.getSpan());
		    	break;
	    	default:
	    		break;
	    }
	    
	    this.pack();
	}
	
	private void handleData(JsonArray data) {
		if(data.size() > 0) {
		    XYSeries series = new XYSeries("");
		    Data last;
		    
			for(Object obj: data) {
				Data tmp = Json.decodeValue(obj.toString(), Data.class);
				series.add(tmp.getTime(), tmp.getValue());
			}
			
		    //Add series to dataset
			this.dataset.removeAllSeries();
		    this.dataset.addSeries(series);
	    
	    	last = Json.decodeValue(data.getJsonObject(0).toString(), Data.class);
	    	this.updateUI(last);
	    }
	}
	
	public static void main(String[] args) {
		new Client("Dam Dashboard", "fe5668dad5d3.ngrok.io");
	}

}

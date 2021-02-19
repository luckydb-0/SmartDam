package dam_dashboard;

import java.awt.Dimension;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.concurrent.TimeUnit;

import javax.swing.JFrame;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import io.vertx.core.Vertx;
import io.vertx.core.json.Json;
import io.vertx.core.json.JsonArray;
import io.vertx.ext.web.client.WebClient;

public class Client extends JFrame {
	
	private static final long serialVersionUID = 3672498792400844882L;
	private XYSeriesCollection dataset;
	
	public Client(String title) {
		super(title);
		this.dataset = new XYSeriesCollection();
		this.initClient();
		
		JFreeChart chart = ChartFactory.createXYLineChart(
		        title,
		        "Tempo",
		        "Distanza rilevata",
		        this.dataset,
		        PlotOrientation.VERTICAL,
		        true, true, false);
		//XYPlot plot = (XYPlot) chart.getPlot();
		
		// Create Panel
	    ChartPanel panel = new ChartPanel(chart);
	    setContentPane(panel);
	    this.setSize(600, 400);
	    this.pack();
	    this.setVisible(true);
	    
	}
	
	private void initClient() {
		String host = "41bede35c21b.ngrok.io";
		int port = 80;

		Vertx vertx = Vertx.vertx();

		WebClient client = WebClient.create(vertx);
		
		System.out.println("Getting data items... ");
		client
		  .get(port, host, "/api/data")
		  .send()
		  .onSuccess(res -> { 
			  System.out.println("Getting - Received response with status code: " + res.statusCode());			  
			  JsonArray response = res.bodyAsJsonArray();
			  this.handleData(response);
		  })
		  .onFailure(err -> System.out.println("Something went wrong " + err.getMessage()));
	}

	private void handleData(JsonArray data) {	    
	    XYSeries series = new XYSeries("");

		for(Object obj: data) {
			Data tmp = Json.decodeValue(obj.toString().replace("time", "timestamp"), Data.class);
			series.add(TimeUnit.MILLISECONDS.toSeconds(tmp.getTimestamp()), tmp.getValue());
		}
		
	    //Add series to dataset
	    this.dataset.addSeries(series);
	    
	    //this.updatePlot(dataset);
	}
	
	
	public static void main(String[] args) {
		Client client = new Client("Dam dashboard");
	}
	

}

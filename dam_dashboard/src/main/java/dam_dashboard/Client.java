package dam_dashboard;

import java.io.FileReader;

import javax.swing.JFrame;

import org.apache.commons.io.IOUtils;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import io.vertx.core.Vertx;
import io.vertx.core.json.JsonArray;
import io.vertx.ext.web.client.WebClient;

public class Client extends JFrame {
	
	private static final long serialVersionUID = 3672498792400844882L;

	public Client(String title) {
		super(title);
		this.initClient();
		
		XYDataset data = createDataset();
		
		JFreeChart chart = ChartFactory.createXYLineChart(
		        title,
		        "Tempo",
		        "Distanza rilevata",
		        data,
		        PlotOrientation.VERTICAL,
		        true, true, false);
		
		// Create Panel
	    ChartPanel panel = new ChartPanel(chart);
	    setContentPane(panel);
	}
	
	private void initClient() {
		String host = "http://71da3360c5b4.ngrok.io";
		int port = 80;

		Vertx vertx = Vertx.vertx();

		WebClient client = WebClient.create(vertx);
		
		System.out.println("Getting data items... ");
		client
		  .get(port, host, "/api/data")
		  .send()
		  .onSuccess(res -> { 
			  System.out.println("Getting - Received response with status code: " + res.statusCode());
			  System.out.println(res.body());
			  
			  JsonArray response = res.bodyAsJsonArray();
			  this.handleData(response);
		      System.out.println(response.encodePrettily());
		  })
		  .onFailure(err -> System.out.println("Something went wrong " + err.getMessage()));
	}

	private void handleData(JsonArray data) {
		System.out.println(data.getList());
	}
	
	private XYDataset createDataset() {
	    XYSeriesCollection dataset = new XYSeriesCollection();
	    
	    XYSeries series = new XYSeries("");
	    series.add(2, 4);
	    series.add(8, 10);
	    series.add(10, 12);
	    series.add(13, 15);
	    series.add(17, 19);
	    series.add(18, 20);
	    series.add(21, 23);

	    //Add series to dataset
	    dataset.addSeries(series);
	    
	    return dataset;
	  }
	
	public static void main(String[] args) {
		Client client = new Client("Dam dashboard");
	}
	

}

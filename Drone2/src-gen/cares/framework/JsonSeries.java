/*
 * RobotSensorsTimeSeries
 *
 * Generated by Cares generator, written with Acceleo
 * Author: jpb
 */
package cares.framework;

import com.fasterxml.jackson.core.JsonFactory;
import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.core.JsonParser;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class JsonSeries  extends TimeableObject{
	protected JsonGenerator jsonGenerator = null;

	public JsonSeries( String filename, double aFrequency) {
		try {
			String path = filePath( filename);
			//System.out.println("JsonSeries => " + path);
			jsonGenerator = new JsonFactory()
					.createGenerator(new FileOutputStream(path));
			jsonGenerator.writeStartObject();
			jsonGenerator.writeArrayFieldStart("series");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		if (aFrequency <= 0) {
			this.frequency = 1;
		} else {
			this.frequency = aFrequency;
		}
	}
	public String filePath( String filename ) {
		try {
			String path = new java.io.File(".").getCanonicalPath();
			if (OS.isWindows()) {
				path = path + "\\data\\results\\";//"\\data\\hdf5\\"      
		      } else if (OS.isLinux()) {
		      	 //cmd = properties.getProperty("gdalPath") + "/" + command;
					path = path + "/data/results/";//"\\data\\hdf5\\"
		      } else {
		          System.out.println("OS not supported");
		      }
			return path + filename + ".json";
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return "";
		}
		
	}
	public JsonParser getParser( String filename) {
		String path = filePath( filename);
		JsonParser jsonParser;
		try {
			jsonParser = new JsonFactory().createParser(new File( path));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			jsonParser = null;
		}
		return jsonParser;
	}
	public void end() {
		try {
			jsonGenerator.writeEndArray(); //closing serie
			jsonGenerator.writeEndObject();
			jsonGenerator.flush();
			jsonGenerator.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void doStep(int nStep) {
		// TODO Auto-generated method stub
		
	}

}

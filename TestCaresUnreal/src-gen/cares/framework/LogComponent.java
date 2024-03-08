package cares.framework;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Field;

import cares.framework.TimeableObject;
//pyp
public abstract class LogComponent extends TimeableObject {
	private FileWriter outputFile;
	private BufferedWriter dataWriterBuffer;

	private int counter;

	private int usage;
	/*
	protected ArrayList<String> firstMethods = null;
	protected ArrayList<String> firstTypes = null;
	protected ArrayList<String> secondMethods = null;
	protected ArrayList<String> secondTypes = null;
	*/
	
	public LogComponent(String filename, double aFrequency) {
		//firstMethods = new ArrayList<String>();
		//firstTypes = new ArrayList<String>();
		//secondMethods = new ArrayList<String>();
		//secondTypes = new ArrayList<String>();

		try {
			String path = filePath( filename);
			outputFile = new FileWriter(path);
			dataWriterBuffer = new BufferedWriter(outputFile);
			open();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		counter = 0;
		if (aFrequency <= 0) {
			this.frequency = 1;
		} else {
			this.frequency = aFrequency;
		}
		usage = 0;
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
			return path + filename + ".csv";
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return "";
		}
		
	}

	public void open() {
		counter = 0;
		usage++;
	}
	public abstract void WriteFirstLine() throws Exception;
	
	public String writeHeadColumn( String s, Field f) {
		return s;
	}

	public boolean close() {
		if (usage <= 1) {
			try {
				dataWriterBuffer.write("\n");
			} catch (IOException e) {
			}
			if (dataWriterBuffer != null) {
				try {
					dataWriterBuffer.close();
				} catch (IOException e) {
					System.err.println("(OUTPUTFILE) Error Closing Outputstream");
					return false;
				}
			}
			if (outputFile != null) {
				try {
					outputFile.close();
				} catch (IOException e) {
					System.err.println("(OUTPUTFILE) Error Closing File : " + outputFile);
					return false;
				}
			}
		}
		return (usage == 1);
	}

	public void writeNames(String... names) {
		String theNames = "";
		for (String name : names) {
			theNames += name + ";";
		}
		this.write(theNames);
	}

	public void writeNewValues(Double... values) {
		String theValues = "";
		if (frequency == 1 || counter == 0) {
			for (Double value : values) {
				theValues += value + ";";
			}
			this.write(theValues);
		}
	}

	public void writeNewValues(Long... values) {
		String theValues = "";
		if (frequency == 1 || counter == 0) {
			for (Long value : values) {
				theValues += value + ";";
			}
			this.write(theValues);
		}
	}

	protected void write(String value) {
		if (counter == 0 && usage <= 1) {
			try {
				dataWriterBuffer.write(value);
				dataWriterBuffer.flush();
			} catch (IOException e) {
				System.err.println("(OUTPUTFILE) Failed to Write");
			}
		}
	}

	public void endLine() {
		if (counter == 0 && usage <= 1) {
			try {
				dataWriterBuffer.write("\n");
				dataWriterBuffer.flush();
			} catch (IOException e) {
				System.err.println("(OUTPUTFILE) Failed to Write");
			}
		}
		counter++;
		if (counter == frequency) {
			counter = 0;
		}
	}


	public void timeStamp(long currentMS) {
		if (counter == 0 && usage <= 1) {
			writeNewValues(currentMS);
		}
	}
	
}

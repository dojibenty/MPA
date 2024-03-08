Declaration core {
	types {
		long(CInt);
		double(CDouble);
		bool(CBoolean);
		string(CString);
		void(Void);
		
		Record Vector3 {
			double x;
			double y;
			double z;
		};
		
		Record WindData {
			Vector3 position;
			Vector3 force;
		};
	}
}
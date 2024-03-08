Declaration Drone {
	leafComponentTypes {
		LeafComponentType Drone {
			inputs { "core.Vector3" newLocation; }
			outputs { "core.Vector3" location; }
			parameters { "core.double" speed; "core.Vector3" currentLocation; }
		}
		LeafComponentType Manager {
			inputs { "core.Vector3" drLocation; }
			outputs { "core.Vector3" newLocation; }
			parameters { "core.Vector3" direction; }
		}
	}
}
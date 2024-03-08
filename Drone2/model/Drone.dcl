Declaration Drone {
	leafComponentTypes {
		LeafComponentType Drone {
			inputs { "core.Vector3" force; }
			outputs { "core.Vector3" position; }
			parameters { "core.double" speed; "core.Vector3" direction; "core.Vector3" drPosition; }
		}
		LeafComponentType Wind {
			inputs { "core.Vector3" position; }
			outputs { "core.Vector3" force; }
			parameters { "core.WindData" windData; }
		}
	}
}
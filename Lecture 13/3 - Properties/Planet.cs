﻿using System;
using System.Collections.Generic;
using System.Text;

namespace Properties {
    public class Body {

        public Body(string name) {
            this.Name = name;
        }

        // Manually created property with backing private variable
        // Usefull if get/set actualy does any work other than boilerplate
        // store/return
        private long radius;
        /// <summary>
        /// Representing Orbital Radius in kilometers
        /// </summary>
        public long Radius {
            get {
                return radius;
            }
            set {
                radius = value;
            }
        }

        // Automatically implemented property
        // Clean, easy to read. Backing field is being
        // auto-generated by compiler. Recommended
        // for boilerplate getter/setter, can easily be converted
        // to manually implemented without breaking anything
        /// <summary>
        /// Orbital period in days
        /// </summary>
        public int Period { get; set; }


        // Read only property. Usefull for returning a calculated value
        // or if the value is set once in the constructor
        /// <summary>
        /// Orbital Velocity
        /// </summary>
        public double Velocity {
            get {
                if (Period == 0) return 0;
                return Radius * 2 * Math.PI / Period;
            }
        }

        // Property with protected set. (Could just as well have been private)
        /// <summary>
        /// Name of Body
        /// </summary>
        public string Name { get; protected set; }

        // Indexer
        /// <summary>
        /// List of orbiting bodies (moons)
        /// </summary>
        Body[] moons = new Body[100];
        public Body this[int i] {
            get {
                return moons[i];
            }
            set {
                moons[i] = value;
            }
        }


    }
}
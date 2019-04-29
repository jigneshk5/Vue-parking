<template>
  <v-app>
    <v-container grid-list-md text-xs-center>
        <v-layout row wrap>
            <v-flex xs12>
                <gmap-autocomplete placeholder="Search for parking" @place_changed="setPlace">
                </gmap-autocomplete>
            </v-flex>
        </v-layout>
    </v-container>
    <v-container grid-list-md text-xs-center class="pt-0">
      <v-layout row wrap>
        <v-flex xs8>
          <gmap-map :center="center" :zoom="15" style="height: 600px">
            <gmap-marker
              v-for="(m,index) in markers"
              :key="index"
              :position="m.position"
              :clickable="true"
              :draggable="true"
              @click="center=m.position"
            ></gmap-marker>
            <Gmap-Marker
              v-if="this.place"
              label="&#x2605;"
              :position="{
                lat: this.place.geometry.location.lat(),
                lng: this.place.geometry.location.lng(),
                }"
            >
            </Gmap-Marker>
          </gmap-map>
        </v-flex>
        <v-flex xs4>
          <v-card height="100%">
            <v-container fluid grid-list-lg>
              <v-layout row wrap>
                <v-flex xs12>
                  <v-card color="primary" class="white--text">
                    <v-card-title primary-title>
                      <div>
                        <div class="headline">Kailash hospital parking</div>
                        <div class="pt-2">
                          <v-chip color="green" text-color="white">
                            <v-avatar class="green darken-4">10</v-avatar>Available
                          </v-chip>
                          <v-chip color="red" text-color="white">
                            <v-avatar class="green darken-4">15</v-avatar>Strength
                          </v-chip>
                        </div>
                      </div>
                    </v-card-title>
                    <v-card-actions class="pb-3">
                      <v-btn block round color="blue-grey" dark>Book now</v-btn>
                    </v-card-actions>
                  </v-card>
                </v-flex>
              </v-layout>
            </v-container>
          </v-card>
        </v-flex>
      </v-layout>
    </v-container>
  </v-app>
</template>

<script>
import { load, Map, Marker } from "vue2-google-maps";
export default {
  components: {
    gmapMap: Map,
    gmapMarker: Marker
  },
  data() {
    return {
      center: { lat: 28.4744, lng: 77.504 },
      markers: [],
      place: null
    };
  },
  methods: {
    setPlace(place) {
      this.place = place;
    },
    usePlace(place) {
      if (this.place) {
        this.markers.push({
          position: {
            lat: this.place.geometry.location.lat(),
            lng: this.place.geometry.location.lng()
          }
        });
        this.place = null;
      }
    }
  }
};
</script>
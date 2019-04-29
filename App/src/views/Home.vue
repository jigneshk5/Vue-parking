<template>
  <v-app>
    <v-navigation-drawer temporary v-model="sideNav" fixed clipped app>
      <v-toolbar flat class="transparent">
        <v-list class="pa-0">
          <v-list-tile avatar>
            <v-list-tile-avatar>
              <img v-bind:src="photo">
            </v-list-tile-avatar>
            <v-list-tile-content>
              <v-list-tile-title>{{name}}</v-list-tile-title>
            </v-list-tile-content>
          </v-list-tile>
        </v-list>
      </v-toolbar>
      <v-list class="pt-0" dense>
        <v-divider></v-divider>
        <v-list-tile v-for="item in menuItems" :key="item.title" router :to="item.link">
          <v-list-tile-action>
            <v-icon color="indigo">{{item.icon}}</v-icon>
          </v-list-tile-action>
          <v-list-tile-content>{{item.title}}</v-list-tile-content>
        </v-list-tile>
      </v-list>
    </v-navigation-drawer>
    <v-toolbar dark color="primary">
      <v-toolbar-side-icon @click.native.stop="sideNav=!sideNav"></v-toolbar-side-icon>
      <v-toolbar-title class="headline text-uppercase">
        <router-link to="/" tag="span" style="cursor:pointer">RENTAL PARKING</router-link>
      </v-toolbar-title>
      <v-spacer></v-spacer>
      <v-btn icon>
        <v-icon>my_location</v-icon>
      </v-btn>
      <router-link to="/live">
        <v-btn icon>
          <v-icon>event</v-icon>
        </v-btn>
      </router-link>
      <div>
        <v-btn v-model="logout" @click="logOut" color="error">LOGOUT</v-btn>
      </div>
    </v-toolbar>
    <Googlemaps></Googlemaps>
  </v-app>
</template>

<script>
import Googlemaps from "../components/googlemaps.vue";
import firebase from "firebase";
export default {
  name: "Home",
  data() {
    return {
      address: "",
      sideNav: false,
      logout: false,
      menuItems: [
        { icon: "add", title: "Add Parking", link: "/parking/new" },
        { icon: "add", title: "Parking Status", link: "/parking/status" },
        { icon: "person", title: "Profile", link: "/profile" },
        { icon: "face", title: "Sign Up", link: "/signup" },
        { icon: "lock_open", title: "Sign In", link: "/signin" }
      ],
      photo: "",
      userId: "",
      name: "",
      email: "",
      user: {}
    };
  },
  components: {
    Googlemaps
  },
  mounted() {
    // To demonstrate functionality of exposed component functions
    // Here we make focus on the user input
    this.$refs.address.focus();
  },
  created() {
    var vm = this;
    firebase.auth().onAuthStateChanged(function(user) {
      if (user) {
        vm.logout = !vm.logout;
        vm.user = user;
        vm.name = vm.user.displayName;
        vm.email = vm.user.email;
        vm.photo = vm.user.photoURL;
        vm.userId = vm.user.uid;
      }
    });
  },
  methods: {
    logOut() {
      firebase.auth().signOut();
    },
    getAddressData(addressData, placeResultData, id) {
      this.address = addressData;
    }
  }
};
</script>

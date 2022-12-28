<script lang="ts">
  import { Icon } from "@smui/common";
  import IconButton from "@smui/icon-button/src/IconButton.svelte";
  import Paper from "@smui/paper/src/Paper.svelte";
  import Ripple from "@smui/ripple";
  import { onMount } from "svelte";

  let isDeleting = false;
  let colors = [];

  const toggleIsDeleting = () => (isDeleting = !isDeleting);

  const deleteColor = (indexToRemove: number) => {
    colors = colors.filter((color, index) => index !== indexToRemove);

    localStorage.setItem("colors", JSON.stringify(colors));
  };

  onMount(() => {
    colors = JSON.parse(localStorage.getItem("colors")) ?? [];
  });
</script>

<div
  style="display:flex;flex-wrap:wrap;justify-content:center;gap:40px;padding:10px;"
>
  {#each colors as color, index (index)}
    <div style="position:relative">
      <Paper variant="raised" style="padding:0;border-radius:4px">
        <div
          use:Ripple={{ surface: true, color: "primary" }}
          style={`width:40px;height:40px;border-radius:4px;cursor:pointer;background-color:rgb(${color.r},${color.g},${color.b})`}
        />
        {#if isDeleting}
          <div
            on:click={() => deleteColor(index)}
            style="background-color:#f00;position:absolute;top:-10px;right:-10px;width:20px;height:20px;border-radius:10px;cursor:pointer"
          >
            <Icon
              style="font-size:18px;color:#fff;margin-top:1px"
              class="material-icons">delete</Icon
            >
          </div>
        {/if}
      </Paper>
    </div>
  {/each}
  <div style="position:fixed;right:20px;bottom:60px;">
    <IconButton on:click={toggleIsDeleting} color="primary"
      ><Icon class="material-icons">{isDeleting ? "check" : "delete"}</Icon
      ></IconButton
    >
  </div>
</div>

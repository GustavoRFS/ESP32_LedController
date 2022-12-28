<script lang="ts">
  import Ripple from "@smui/ripple";
  import Paper, { Title, Subtitle } from "@smui/paper";

  const effects = [
    { title: "Strobe", subtitle: "Pisca Pisca", message: "S" },
    {
      title: "Smooth",
      subtitle: "Troca as cores de forma suave",
      message: "s",
    },
    {
      title: "Flash",
      subtitle: "Pisca rapidamente a última cor selecionada",
      message: "F",
    },
    {
      title: "Fade monocolor",
      subtitle: "Pisca lentamente a última cor selecionada",
      message: "f",
    },
    { title: "Fade", subtitle: "Pisca lentamente algumas cores", message: "e" },
  ];

  const sendMessage = console.log;
</script>

<div style="display: flex;flex-wrap:wrap;justify-content:center;gap:40px">
  {#each effects as effect}
    <div
      on:click={() => sendMessage(effect.message)}
      use:Ripple={{ surface: true, color: "primary" }}
      style="padding:2px;border-radius:6px;cursor:pointer;min-width:400px"
    >
      <Paper>
        <Title>{effect.title}</Title>
        <Subtitle>{effect.subtitle}</Subtitle>
      </Paper>
    </div>
  {/each}
</div>
